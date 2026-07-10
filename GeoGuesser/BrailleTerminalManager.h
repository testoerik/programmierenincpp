#include "./TerminalManager.h"
#include <array>
#include <ncursesw.h>
#include <vector>
#pragma once
class BrailleTerminalManager : public TerminalManager {
public:
  void drawPixel(int row, int col, int color) override;
  // Dive one col into 2 cols and one row into 8 rows so we can draw a Braille.
  void drawBraillePattern(float row, float col, int color);

private:
  // Container which contains all braille pixel.
  std::vector<std::array<int, 8>> containerOfBraillePixels_;
  // Constructor which initializes the braille pixel and the container.
  BrailleTerminalManager();
  // Physical coordinates.
  int terminalX_;
  int terminalY_;
};
