// Created by eh295

#pragma onnce
#include <ncurses.h>
#include <unistd>

// Dimensions of the window.
extern int numRows;
extern int numCols;

// Current position
extern int row;
extern int col;

extern bool actualState[];
extern bool nextState[];

extern bool* a;
extern bool* n;

extern int posX;
extern int posY;

extern int numSteps;
extern int numAliveCells;

extern bool StateGame;

// Initializing the terminal and the field dimensions.
void initTerminal();
void initGame();

void ShowState();

int numAliveNeighboors(int row, int col);

void updateState();

bool processUserInput(int keycode);


