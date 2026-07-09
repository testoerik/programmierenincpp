// Copyright 2026, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>,
//         Christoph Ullinger <ullingec@cs.uni-freiburg.de>.

#pragma once

#include "./TerminalManager.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <ft2build.h>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include FT_FREETYPE_H

// A 2D cell with size_t coordinates, used as the key type of
// OpenGLTerminalManager's charsToDraw_ map below. Named distinctly from
// MockTerminalManager's own (unrelated) Cell type so the two can't collide if
// both headers were ever included in the same translation unit.
class OpenGLCell {
public:
  size_t row_;
  size_t col_;

  OpenGLCell(size_t row, size_t col) : row_{row}, col_{col} {}
  bool operator==(const OpenGLCell &other) const {
    return row_ == other.row_ && col_ == other.col_;
  }
};

template <> struct std::hash<OpenGLCell> {
  size_t operator()(const OpenGLCell &p) const {
    auto hash1 = std::hash<size_t>{}(p.row_);
    auto hash2 = std::hash<size_t>{}(p.col_);
    if (hash1 != hash2)
      return hash1 ^ hash2;
    // If hash1 == hash2, their XOR is zero.
    return hash1;
  }
};

// A TerminalManager that draws pixels in a desktop window via OpenGL/GLFW,
// with text rendered using FreeType. The logical grid is size_ x size_
// (square), independent of the window's actual pixel dimensions.
class OpenGLTerminalManager : public TerminalManager {
public:
  // Constructor: open a window and set up OpenGL/FreeType state.
  OpenGLTerminalManager();

  // Destructor: close the window.
  ~OpenGLTerminalManager();

  // Get input from the user.
  UserInput getUserInput() override;

  // Draw a pixel at the given position in the given color.
  void drawPixel(int row, int col, int color) override;

  // Draw a string at the given position in the given color.
  void drawString(int row, int col, const char *output, int color) override;

  // Refresh the screen.
  void refresh() override;

  // Get the dimensions of the screen.
  int numRows() const override { return size_; }
  int numCols() const override { return size_; }

private:
  // The number of logical rows and columns (the pixel grid is square).
  int size_ = 1000;
  GLFWwindow *window_;
  // Input collected by the GLFW callbacks below, drained by getUserInput().
  std::queue<int> keypresses_;
  std::queue<std::pair<int, int>> mouseClicks_; // (row, col)
  // The cursor position as of the most recent GLFW motion event, updated by
  // its own callback. The mouse-button callback reads this instead of
  // calling glfwGetCursorPos() (see its comment for why).
  double lastCursorX_ = 0;
  double lastCursorY_ = 0;

  // One RGB triple per logical pixel, uploaded as a texture in refresh().
  std::vector<float> pixels_;
  GLuint texture_;

  // Kept alive for the object's lifetime (not just the constructor) so
  // glyphs beyond the ASCII set warmed up there can still be loaded lazily,
  // e.g. the umlauts in German state names.
  FT_Library ft_;
  FT_Face face_;
  struct Character {
    unsigned int textureId; // ID handle of the glyph texture
    std::tuple<unsigned int, unsigned int> size; // Size of glyph
    std::tuple<unsigned int, unsigned int>
        bearing;    // Offset from baseline to left/top of glyph
    FT_Pos advance; // Offset to advance to next glyph
  };
  // Keyed by Unicode code point (not by raw char/byte), since a code point
  // like an umlaut is multiple bytes in the UTF-8 strings drawString()
  // receives.
  std::unordered_map<unsigned int, Character> characters_;

  // One buffered drawString() character, replayed in refresh(). `scale`
  // shrinks the glyph (see drawString()) so a string longer than would
  // otherwise fit in the available columns is drawn smaller instead of
  // being cut off.
  struct CharDraw {
    unsigned int codepoint;
    int color;
    float scale;
  };
  std::unordered_map<OpenGLCell, CharDraw> charsToDraw_;

  // Return the Character for the given Unicode code point, loading and
  // caching it first if this is the first time it's been requested.
  const Character &getCharacter(unsigned int codepoint);

  void renderText(unsigned int codepoint, int col, int row, int color,
                  float scale);
};
