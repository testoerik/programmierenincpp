
class TerminalManager {
  // The total number of logical pixels on the screen.
  int numRows_;
  int numCols_;
  
  // Initialize the terfimal for use with ncurses commands.
  void setup();

  // Draw a pixel at the given logical position in the given color.
  void drawPixel(int row, int column, int color);
};
