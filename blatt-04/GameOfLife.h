// Created by eh295

#pragma once
#include <ncurses.h>
#include <unistd.h>

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

int numAliveNeighbors(int row, int col);

void updateState();

bool processUserInput(int keycode);


