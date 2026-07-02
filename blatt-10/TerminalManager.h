#include <stddef.h>
#pragma once

class TerminalManager {
public:
  // Constructor
  TerminalManager();
  virtual void drawPixel(int row, int col, bool inverse, float intensity);
  virtual void refresh();
  virtual ~TerminalManager();

  // Get the dimensions of the screen.
  int numRows() const { return numRows_; }
  int numCols() const { return numCols_; }

private:
  // Convert an intensity in the range [0.0, 1.0] to the index of the
  // corresponding color
  size_t convertIntensityToColor(float intensity) const;

protected:
  // The number of "logical" rows and columns of the screen.
  int numRows_, numCols_;
};
