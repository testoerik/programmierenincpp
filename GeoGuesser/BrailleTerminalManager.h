#include "./TerminalManager.h"
#include <ncursesw.h>
#include <vector>
#pragma once
class BrailleTerminalManager : public TerminalManager {
public:
  void drawPixel(int row, int col, int color) override;
  // Dive one col into 2 cols and one row into 8 rows so we can draw a Braille.
  void drawBraillePattern(float row, float col, int color);
private:
  std::vector<std::vector<int>>
      containerOfBraillePixels((numRows() * numCols()) / 8);
  std::vector<int> braillePixel(8) = {0, 0, 0, 0, 0, 0, 0, 0};
  // Constructor.
  BrailleTerminalManager();
  // Physical coordinates.
  int terminalX_;
  int terminalY_;
};
