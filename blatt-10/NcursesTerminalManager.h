// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//

#pragma once
#include "./TerminalManager.h"
#include <cstddef>

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
class NcursesTerminalManager : public TerminalManager {
public:
  NcursesTerminalManager();
  ~NcursesTerminalManager();
  UserInput getUserInput();
  void drawPixel(int row, int col, bool inverse, float intensity) override;
  void refresh() override;
  void drawString(int row, int col, const char *output, float intensity = 1.0);
  int numColors();

private:
  size_t convertIntensityToColor(float intensity) const;
};
