// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//

#pragma once
#include "./TerminalManager.h"
#include <cstddef>

// Class for the input from the user.
class UserInput {
public:
  bool isKeyUp();
  bool isKeyDown();
  bool isKeyLeft();
  bool isKeyRight();
  // The code of the key pressed.
  int keycode_;
  // Was the event a mousecklick.
  bool isMouseclick_;
  // If the event was a mousecklick, then the coordinates
  // of the mouseclick are stored here.
  int mouseX_ = -1;
  int mouseY_ = -1;
};

// A class managing the input and output via the terminal, using ncurses.
class NcursesTerminalManager {
public:
  // Constructor: initialize the terminal for use with ncurses.
  NcursesTerminalManager();

  // Destructor: Clean up the screen.
  ~NcursesTerminalManager();

  // Get input from the user.
  UserInput getUserInput();

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  void drawPixel(int row, int col, bool inverse, float intensity) override;

  // Draw a string at the given position and with the given intensity.
  // The intensity has to be in [0.0, 1.0]
  void drawString(int row, int col, const char *output, float intensity = 1.0);

  // Refresh the screen.
  void refresh() override;

  // Get the number of colors.
  int numColors();

private:
  // Convert an intensity in the range [0.0, 1.0] to the index of the
  // corresponding color
  size_t convertIntensityToColor(float intensity) const;
};
