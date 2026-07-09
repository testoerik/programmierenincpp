
#pragma once

#include "./TerminalManager.h"

// A class managing the input and output via the terminal, using ncurses.
class NCursesTerminalManager : public TerminalManager {
public:
  // Constructor: initialize the terminal for use with ncurses.
  NCursesTerminalManager();

  // Destructor: Clean up the screen.
  ~NCursesTerminalManager();

  // Get input from the user.
  UserInput getUserInput() override;

  // Draw a pixel at the given position in the given color.
  void drawPixel(int row, int col, int color) override;

  // Draw a string at the given position in the given color.
  void drawString(int row, int col, const char *output, int color) override;

  // Refresh the screen.
  void refresh() override;

  // Get the dimensions of the screen.
  int numRows() const override { return numRows_; }
  int numCols() const override { return numCols_; }

private:
  // The number of "logical" rows and columns of the screen.
  int numRows_;
  int numCols_;
  // The number of usable palette colors (see ctor for the color pair
  // layout this backs).
  int numColors_;
};
