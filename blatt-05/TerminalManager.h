// Author: eh295
#pragma once

class UserInput {
public:
  int keycode_;

  bool isKeySpace();
  bool isKeyS();
  bool isKeyR();
  bool isKeyQ();
  bool isKeyG();
  bool isKeyMouse();
};

class TerminalManager {
private:
  // The total number of pixels on the screen.
  int numRows_;
  int numCols_;

public:
  // Getters for the screen dimensions.
  int numRows() { return numRows_; }
  int numCols() { return numCols_; }

  // The colors supported by our terminal manager.
  static int White;
  static int Red;
  static int Green;

  // Initialize the terminal for use with ncurses commands.
  TerminalManager();

  // Reset the terminal.
  ~TerminalManager();

  // Refresh the screen.
  void refresh();

  // Draw a pixel at the given logical position in the given color.
  void drawPixel(int col, int row, int color);

  // Read user keyboard or mouse input.
  UserInput getUserInput();
};
