// Created by eh295

#pragma once
#include "./TerminalManager.h"
#include <ncurses.h>
#include <unistd.h>

class GameOfLife {
public:
  // Current position of each cell.
  int posX_;
  int posY_;
  bool *actlStPtr_ = actualState_;
  bool *nxtStPtr_ = nextState_;
  
  // Play Game of Life.
  void play();

private:
  static const int MAX_NUM_CELLS = 10'000;
  bool actualState_[MAX_NUM_CELLS];
  bool nextState_[MAX_NUM_CELLS];

  // We will need these two variables to iterate trough our field.
  int row_;
  int col_;

  //
  int numSteps_;
  int numAliveCells_;

  // State of the game: Is it playing (true) or paused (paused) ?
  bool stateGame_;

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
};
