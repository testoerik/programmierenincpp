#pragma once
class UserInput {
public:
  int keycode_;

  bool isEscape();
  bool isKeyUp();
  bool isKeyDown();
  bool isKeyLeft();
  bool isKeyRight();
};
class TerminalManager {
private:
  int numRows_;
  int numCols_;

public:
  // Colors for our terminal manager.
  static int Green;
  static int Red;
  // Getter function for numRows_ and numCols_.
  int numRows() { return numRows_; }
  int numCols() { return numCols_; }
  void drawPixel(int y, int x, int color);
  void setup();
  // Clean the screen.
  void cleanup();
  // Refresh the screen.
  void refresh();
  // Read user keyboard or mouse input.
  UserInput getUserInput();
};
