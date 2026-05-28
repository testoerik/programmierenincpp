// Created by eh295

#pragma once
#include "./TerminalManager.h"
#include <ncurses.h>
#include <unistd.h>

class GameOfLife {
public:
  // Current position of each cell
  int posX_;
  int posY_;
  
  bool *a = actualState;
  bool *n = nextState;
  bool actualState[];
  bool nextState[];
};

// We will need these two variables to iterate trough our field.
extern int row;
extern int col;


// Two pointers a and n.
// a points to the entry in the actualState array.
// n points to the entry in the nextState array.
extern bool *a;
extern bool *n;

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
