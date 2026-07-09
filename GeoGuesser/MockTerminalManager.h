#pragma once

#include "./TerminalManager.h"
#include <cstddef>
#include <unordered_map>

// A 2D cell with size_t coordinates, used as the key type of
// MockTerminalManager's drawnPixels_ map below.
class Cell {
public:
  size_t row_;
  size_t col_;

  Cell(size_t row, size_t col) : row_{row}, col_{col} {}
  // To store the Cells in a hashMap we have
  // to define the equality == between Cells.
  bool operator==(const Cell &other) const {
    return row_ == other.row_ && col_ == other.col_;
  }
};

// We use Cell as the key type to a hash map, so we have to define
// a hash function.
template <> struct std::hash<Cell> {
  size_t operator()(const Cell &p) const {
    auto hash1 = std::hash<size_t>{}(p.row_);
    auto hash2 = std::hash<size_t>{}(p.col_);
    return 2 * hash1 ^ hash2;
  }
};

// An implementation of a terminal Manager that "draws" the pixels
// to a 2d-Array for testing/mocking purposes
class MockTerminalManager : public TerminalManager {
private:
  // This map stores the color of each pixel drawn using the drawPixel method.
  std::unordered_map<Cell, int> drawnPixels_;
  int numRows_;
  int numCols_;

public:
  // Construct with the given inumber of rows and cols.
  MockTerminalManager(int numRows, int numCols)
      : numRows_{numRows}, numCols_{numCols} {};

  ~MockTerminalManager() = default;

  // Draw a pixel at the given position in the given color.
  void drawPixel(int row, int col, int color) override;

  // Nothing to do for "drawString"
  void drawString(int, int, const char *, int) override {};

  // Nothing to do for "refresh"
  void refresh() override {};

  // Get the dimensions of the screen.
  int numRows() const override { return numRows_; }
  int numCols() const override { return numCols_; }

  // Returns true iff there previously was a call to
  // drawPixel(row, col).
  bool isPixelDrawn(int row, int col) const;

  // Returns the "color" argument of the last call to
  // drawPixel(row, col);
  // Throws an exception if there was no such call.
  int getColor(int row, int col) const;
};
