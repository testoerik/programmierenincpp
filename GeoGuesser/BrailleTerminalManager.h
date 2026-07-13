#include "./TerminalManager.h"
#include <array>
#include <ncursesw.h>
#include <vector>
#pragma once
class BrailleTerminalManager : public TerminalManager {
public:
  void drawPixel(int row, int col, int color) override;
  
  void drawBraillePattern(float row, float col, int color);
  
  void computeBraillePattern(std::vetor<struct>);
  // Getter-Funktionen um die Bildschirm-Dimensionen (Spaltenzahl und Zeilenzahl) zu bekommen.
  int numRows() const override { return numRows_; }
  int numCols() const override { return numCols_; }
  
private:
  // Container which contains all braille pixel.
  std::vector<std::array<int, 8>> containerOfBraillePixels_;
  // Constructor which initializes the braille pixel and the container.
  BrailleTerminalManager(std::vector<struct>);
  // Physical coordinates.
  int terminalX_;
  int terminalY_;
};
