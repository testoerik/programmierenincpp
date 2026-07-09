// Copyright 2026, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>,
//         Christoph Ullinger <ullingec@cs.uni-freiburg.de>.

#include "./OpenGLTerminalManager.h"
#include <algorithm>
#include <cstring>
#include <ncurses.h> // for the COLOR_* and KEY_* constants used below
#include <stdexcept>

constexpr int PIXEL_SIZE = 300;
// Horizontal spacing (in logical columns) between consecutive characters
// drawn by drawString().
constexpr int GLYPH_ADVANCE = 50;

namespace {
// Decode the UTF-8 code point starting at s[i], advancing i past all of its
// bytes.
unsigned int decodeUtf8(const char *s, size_t len, size_t &i) {
  unsigned char lead = static_cast<unsigned char>(s[i]);
  int continuationBytes;
  unsigned int codepoint;
  if ((lead & 0x80) == 0x00) {
    codepoint = lead;
    continuationBytes = 0;
  } else if ((lead & 0xE0) == 0xC0) {
    codepoint = lead & 0x1F;
    continuationBytes = 1;
  } else if ((lead & 0xF0) == 0xE0) {
    codepoint = lead & 0x0F;
    continuationBytes = 2;
  } else if ((lead & 0xF8) == 0xF0) {
    codepoint = lead & 0x07;
    continuationBytes = 3;
  } else {
    ++i;
    return lead;
  }
  ++i;
  for (int k = 0; k < continuationBytes && i < len &&
                  (static_cast<unsigned char>(s[i]) & 0xC0) == 0x80;
       ++k, ++i) {
    codepoint = (codepoint << 6) | (static_cast<unsigned char>(s[i]) & 0x3F);
  }
  return codepoint;
}

// The same palette (the 8 basic ANSI colors identified by ncurses.h's
// COLOR_BLACK..COLOR_WHITE, plus a "bright black"/grey at 8 and orange at 9)
// that BrailleTerminalManager and NCursesTerminalManager use for their color
// arguments, translated to RGB triples in [0, 1] for OpenGL.
std::tuple<float, float, float> colorToRgb(int color) {
  switch (color) {
  case COLOR_RED:
    return {1.0f, 0.0f, 0.0f};
  case COLOR_GREEN:
    return {0.0f, 1.0f, 0.0f};
  case COLOR_YELLOW:
    return {1.0f, 1.0f, 0.0f};
  case COLOR_BLUE:
    return {0.0f, 0.0f, 1.0f};
  case COLOR_MAGENTA:
    return {1.0f, 0.0f, 1.0f};
  case COLOR_CYAN:
    return {0.0f, 1.0f, 1.0f};
  case COLOR_WHITE:
    return {1.0f, 1.0f, 1.0f};
  case 8: // grey
    return {0.5f, 0.5f, 0.5f};
  case 9: // orange
    return {1.0f, 0.65f, 0.0f};
  case 11: // bright yellow
    return {1.0f, 1.0f, 0.0f};
  case COLOR_BLACK:
  default:
    return {0.0f, 0.0f, 0.0f};
  }
}
} // namespace

// ____________________________________________________________________________
OpenGLTerminalManager::OpenGLTerminalManager() {
  pixels_.assign(static_cast<size_t>(size_) * size_ * 3, 0.0f);
  /* Initialize the library */
  if (!glfwInit()) {
    throw std::runtime_error{"Could not initialize GLFW!"};
  }

  /* Create a windowed mode window and its OpenGL context */
  window_ = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window_) {
    glfwTerminate();
    throw std::runtime_error{"Could not create Window!"};
  }
  glfwSetWindowUserPointer(window_, static_cast<void *>(this));
  /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  // Seed the tracked cursor position (see the cursor-pos callback below) so
  // a click before the very first mouse-move event still has a real
  // position to read, instead of the (0, 0) default.
  glfwGetCursorPos(window_, &lastCursorX_, &lastCursorY_);

  glEnable(GL_TEXTURE_2D);

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // The logical pixel grid (size_ x size_) is usually much higher-resolution
  // than the actual window, so displaying it is a minification. Nearest-
  // neighbor minification just samples one texel per screen pixel and skips
  // the rest, which can skip a whole thin (1-texel-wide) polygon boundary
  // line between samples, leaving visible gaps. Mipmapped linear filtering
  // averages every texel into the sampled result instead, so a thin line
  // still shows up (softened) rather than disappearing.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Auto-regenerate the mipmap chain whenever glTexImage2D uploads a new
  // base level (every frame, since pixels_ just changed). This legacy
  // (pre-GL3) mechanism is used instead of calling glGenerateMipmap()
  // directly because that function isn't available without an extension
  // loader, which this project (all fixed-function/immediate-mode GL calls)
  // doesn't otherwise need.
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Track the cursor position as GLFW reports it move, rather than querying
  // it live from inside the button callback below: glfwPollEvents() (called
  // once per frame, not continuously) can dispatch a backlog of queued OS
  // events at once, and by the time it gets around to the button-press
  // callback, glfwGetCursorPos() would report wherever the mouse is *right
  // now* -- which, if the player moved the mouse in the meantime, is no
  // longer where it was at the moment of the actual click. This callback's
  // parameters are the position as of that specific (already historical)
  // motion event, so as long as GLFW dispatches events in the order they
  // occurred, the button-press callback below always sees the position as of
  // the most recent motion event *before* the click, not after it.
  glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y) {
    auto self =
        static_cast<OpenGLTerminalManager *>(glfwGetWindowUserPointer(window));
    self->lastCursorX_ = x;
    self->lastCursorY_ = y;
  });

  glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button,
                                         int action,
                                         [[maybe_unused]] int mods) {
    if (button != GLFW_MOUSE_BUTTON_1 || action != GLFW_PRESS) {
      return;
    }
    auto self =
        static_cast<OpenGLTerminalManager *>(glfwGetWindowUserPointer(window));
    double cursorX = self->lastCursorX_, cursorY = self->lastCursorY_;
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    auto minmax = std::minmax(windowWidth, windowHeight);
    double viewportX =
        (cursorX - ((minmax.second - windowHeight) / 2)) / minmax.first;
    double viewportY =
        (cursorY - ((minmax.second - windowWidth) / 2)) / minmax.first;
    if (viewportX >= 1 || viewportY >= 1 || viewportX < 0 || viewportY < 0) {
      return;
    }
    self->mouseClicks_.push({static_cast<int>(self->numRows() * viewportY),
                             static_cast<int>(self->numCols() * viewportX)});
  });

  glfwSetCharCallback(window_, [](GLFWwindow *window, unsigned int codepoint) {
    if (codepoint > 127) {
      return;
    }
    auto self =
        static_cast<OpenGLTerminalManager *>(glfwGetWindowUserPointer(window));
    self->keypresses_.push(static_cast<int>(codepoint));
  });

  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key,
                                 [[maybe_unused]] int scancode, int action,
                                 [[maybe_unused]] int mods) {
    if (action != GLFW_PRESS) {
      return;
    }
    auto self =
        static_cast<OpenGLTerminalManager *>(glfwGetWindowUserPointer(window));
    // Translate GLFW's key codes to the ncurses key codes that the shared
    // UserInput::isKeyUp() etc. (defined once in TerminalManager.cpp) check
    // against, so the same UserInput class works for this GLFW-based backend
    // as well as the ncurses-based ones.
    switch (key) {
    case GLFW_KEY_UP:
      self->keypresses_.push(KEY_UP);
      break;
    case GLFW_KEY_DOWN:
      self->keypresses_.push(KEY_DOWN);
      break;
    case GLFW_KEY_LEFT:
      self->keypresses_.push(KEY_LEFT);
      break;
    case GLFW_KEY_RIGHT:
      self->keypresses_.push(KEY_RIGHT);
      break;
    case GLFW_KEY_ESCAPE:
      self->keypresses_.push(27);
      break;
    default:
      break;
    }
  });

  if (FT_Init_FreeType(&ft_)) {
    throw std::runtime_error{"Could not init FreeType Library"};
  }

  if (FT_New_Face(ft_, "CascadiaMono.ttf", 0, &face_)) {
    throw std::runtime_error{"Failed to load font"};
  }
  FT_Set_Pixel_Sizes(face_, 0, PIXEL_SIZE);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

  // Warm the glyph cache with ASCII, the common case; anything else (e.g. an
  // umlaut) is loaded lazily by getCharacter() on first use. ft_/face_ stay
  // alive for the object's lifetime (torn down in the destructor, not here)
  // to make that possible.
  for (unsigned char c = 0; c < 128; c++) {
    getCharacter(c);
  }
}

// ____________________________________________________________________________
OpenGLTerminalManager::~OpenGLTerminalManager() {
  FT_Done_Face(face_);
  FT_Done_FreeType(ft_);
  glfwTerminate();
}

// ____________________________________________________________________________
const OpenGLTerminalManager::Character &
OpenGLTerminalManager::getCharacter(unsigned int codepoint) {
  auto it = characters_.find(codepoint);
  if (it != characters_.end())
    return it->second;

  if (FT_Load_Char(face_, codepoint, FT_LOAD_RENDER)) {
    throw std::runtime_error{"ERROR::FREETYPE: Failed to load Glyph"};
  }
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // GL_LUMINANCE (not GL_RED) so the fixed-function GL_MODULATE texture env
  // (see renderText()) broadcasts the glyph's coverage value into all of
  // R/G/B rather than just R -- otherwise glColor3f()'s green/blue
  // components would always get multiplied by 0 and text would render as
  // shades of red regardless of the requested color.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, face_->glyph->bitmap.width,
               face_->glyph->bitmap.rows, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE,
               face_->glyph->bitmap.buffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  Character character = {
      texture,
      {face_->glyph->bitmap.width, face_->glyph->bitmap.rows},
      {face_->glyph->bitmap_left, face_->glyph->bitmap_top},
      face_->glyph->advance.x};
  return characters_.emplace(codepoint, character).first->second;
}

// ____________________________________________________________________________
void OpenGLTerminalManager::drawPixel(int row, int col, int color) {
  if (row < 0 || row >= size_ || col < 0 || col >= size_)
    return;
  auto [r, g, b] = colorToRgb(color);
  size_t offset = 3 * (static_cast<size_t>(row) * size_ + col);
  pixels_[offset + 0] = r;
  pixels_[offset + 1] = g;
  pixels_[offset + 2] = b;
}

// ____________________________________________________________________________
void OpenGLTerminalManager::refresh() {
  int width, height;

  glfwGetFramebufferSize(window_, &width, &height);

  auto minmax = std::minmax(width, height);

  int xOffset = (minmax.second - height) / 2;
  int yOffset = (minmax.second - width) / 2;

  // Make viewport guaranteed to be square
  glViewport(xOffset, yOffset, minmax.first, minmax.first);
  /* Render here */
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture_);
  // GL_GENERATE_MIPMAP (set in the ctor) rebuilds the mipmap chain right
  // here, automatically, since this call updates the base mip level.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size_, size_, 0, GL_RGB, GL_FLOAT,
               pixels_.data());

  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(1.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(-1.0f, 1.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  for (const auto &[cell, charDraw] : charsToDraw_) {
    renderText(charDraw.codepoint, static_cast<int>(cell.col_),
               static_cast<int>(cell.row_), charDraw.color, charDraw.scale);
  }
  // Buffered text is only valid for the frame it was drawn in, same as
  // BrailleTerminalManager's pendingText_.
  charsToDraw_.clear();

  /* Swap front and back buffers */
  glfwSwapBuffers(window_);

  /* Poll for and process events */
  glfwPollEvents();
}

// ___________________________________________________________________________
void OpenGLTerminalManager::drawString(int row, int col, const char *output,
                                       int color) {
  if (row < 0 || row >= numRows()) {
    return;
  }

  // Decode the whole string up front: the per-character column step below
  // depends on how many characters there are in total (to fit a long string
  // into the available columns instead of cutting it off), which isn't known
  // until all of them have been decoded.
  size_t len = strlen(output);
  std::vector<unsigned int> codepoints;
  for (size_t i = 0; i < len;)
    codepoints.push_back(decodeUtf8(output, len, i));
  if (codepoints.empty())
    return;

  // GLYPH_ADVANCE columns per character is the normal spacing; if the full
  // string wouldn't fit in the columns available from `col` to the edge of
  // the screen at that spacing, shrink both the spacing and the glyphs
  // themselves (via `scale`) just enough to make it fit, rather than
  // truncating the string.
  int available = numCols() - col;
  int advance = GLYPH_ADVANCE;
  if (available > 0)
    advance = std::min(GLYPH_ADVANCE,
                       available / static_cast<int>(codepoints.size()));
  advance = std::max(advance, 1);
  float scale = static_cast<float>(advance) / GLYPH_ADVANCE;

  for (size_t i = 0; i < codepoints.size(); ++i) {
    int c = col + static_cast<int>(i) * advance;
    if (c < 0 || c >= numCols())
      break;
    charsToDraw_[OpenGLCell{static_cast<size_t>(row), static_cast<size_t>(c)}] =
        {codepoints[i], color, scale};
  }
}

// ___________________________________________________________________________
UserInput OpenGLTerminalManager::getUserInput() {
  // Purely reads events already collected by the GLFW callbacks (populated
  // the last time refresh() called glfwPollEvents()); it does NOT render or
  // swap buffers itself. The caller draws a frame and then calls refresh()
  // exactly once, same as with the ncurses-based backends -- if
  // getUserInput() also rendered a frame (as blatt-10's original did), every
  // loop iteration would flash an empty, not-yet-drawn frame before the
  // caller's real one, which is what made the status text appear to blink.
  UserInput input;
  input.keycode_ = -1;
  if (!keypresses_.empty()) {
    input.keycode_ = keypresses_.front();
    keypresses_.pop();
  } else if (!mouseClicks_.empty()) {
    input.mouseRow_ = mouseClicks_.front().first;
    input.mouseCol_ = mouseClicks_.front().second;
    mouseClicks_.pop();
  }

  if (glfwWindowShouldClose(window_)) {
    // Treat closing the window the same as pressing ESC.
    input.keycode_ = 27;
  }

  return input;
}

// ____________________________________________________________________________
void OpenGLTerminalManager::renderText(unsigned int codepoint, int col, int row,
                                       int color, float scale) {
  // Each cell in charsToDraw_ already holds exactly one code point (see
  // drawString()), so this draws exactly one glyph -- no need for its own
  // horizontal-advance loop.
  glPushMatrix();
  // move to top left from center
  glTranslatef(-1, 1, 0);
  glScalef(2.0f / numRows(), 2.0f / numCols(), 1.0f);
  glTranslatef(col, -row, 0);
  // scale to grid, shrunk further by `scale` if drawString() had to shrink
  // this string to make it fit in its available columns
  glScalef(scale * 50.0 / PIXEL_SIZE, scale * 50.0 / PIXEL_SIZE, 0);
  glTranslatef(50, -230, 0);

  auto [r, g, b] = colorToRgb(color);
  glColor3f(r, g, b);

  const Character &ch = getCharacter(codepoint);

  float xpos = std::get<0>(ch.bearing);
  float ypos =
      static_cast<float>(std::get<1>(ch.bearing)) - std::get<1>(ch.size);
  float w = std::get<0>(ch.size);
  float h = std::get<1>(ch.size);

  glBindTexture(GL_TEXTURE_2D, ch.textureId);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(xpos, ypos);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(xpos + w, ypos);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(xpos + w, ypos + h);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(xpos, ypos + h);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
}
