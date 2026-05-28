// Created by eh295

#pragma once
#include <ncurses.h>
#include <unistd.h>
#include "./TerminalManager.h"
// Dimensions of the window.
extern int numRows;
extern int numCols;

// We will need these two variables to iterate trough our field.
extern int row;
extern int col;

// Two one-dimensional arrays with the states (true or false) of each cell.
// actualState: Is the state of the cell we are looking for alive (true) or dead
// (false) ? nextState: Do we need to change the state of the cell or not ?
extern bool actualState[];
extern bool nextState[];

// Two pointers a and n.
// a points to the entry in the actualState array.
// n points to the entry in the nextState array.
extern bool *a;
extern bool *n;

// posX and posY are the position of each cell.
extern int posX;
extern int posY;

//
extern int numSteps;
extern int numAliveCells;

// State of the game: Is it playing (true) or paused (paused) ?
extern bool stateGame;

// Initializing the terminal and the field dimensions.
void initTerminal();
void initGame();

// Show the state of each cell in the terminal.
void showState();

int numAliveNeighbors(int row, int col);

// In this void function are the game of life rules.
void updateState();

// Handles all the possible user inputs, for example space key for pause or
// playing, 'q' for quit etc.
bool processUserInput(UserInput userInput);
