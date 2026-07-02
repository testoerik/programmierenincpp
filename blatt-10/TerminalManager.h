#pragma once

class TerminalManager {
public:
  virtual void drawPixel(int row, int col, bool inverse, float intensity);
  virtual void refresh();
  virtual ~TerminalManager();
  // Get the dimensions of the screen.
  int numRows() const { return numRows_; }
  int numCols() const { return numCols_; }

protected:
  // The number of "logical" rows and columns of the screen.
  int numRows_, numCols_;
};
