#pragma once
class UserInput {
public:
  int keycode;
	
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
  // Getter function for numRows_ and numCols_.
  int numRows() { return numRows_; }
  int numCols() { return numCols_; }
  void drawPixel(int y, int x, int color);
  void setup();
  
  UserInput userInput_;
};
