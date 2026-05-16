// Created by Erik Hagmüller

#include <ncurses.h>

// Current position (logical coordinates).
extern int row;
extern int col;

// Dimension of the window (logical coordinates).
extern int numRows;
extern int numCols;

// The values of all pixels.
extern bool pixels[];

// Start ncurses
void startNcurses();

// End ncures
void endNcurses();

// Set the value of the given pixel.
void setPixel(int row, int col, bool value);

// Get the value of the given pixel.
bool getPixel(int row, int col);

// Process mouse event. Return true if a mouse event was processed, and
// false otherwise.
bool processMouseEvent(int keycode);

// Draw all pixels.
void drawAllPixels();


