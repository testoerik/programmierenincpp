// Created by eh295

#pragma once
#include "./TerminalManager.h"
#include <ncurses.h>
#include <unistd.h>

class GameOfLife {
private:
  static const int MAX_NUM_CELLS = 10'000;
  bool actualState_[MAX_NUM_CELLS];
  bool nextState_[MAX_NUM_CELLS];
  // Initialize TerminalManager.
  TerminalManager *terminalManager_;
  //
  int numSteps_;
  int numAliveCells_;

  // State of the game: Is it playing (true) or paused (paused) ?
  bool stateGame_;

  // Show the state of each cell in the terminal.
  void showState();

  int numAliveNeighbors(int row, int col);

  // In this void function are the game of life rules.
  void updateState();

  // Handles all the possible user inputs, for example space key for pause or
  // playing, 'q' for quit etc.
  bool processUserInput(UserInput userInput);
public:
  // Two variables to iterate.
  int row_;
  int col_;
  
  bool cellVal_;
  // Constructor
  explicit GameOfLife(TerminalManager *terminalManager_);
  // Current position of each cell.
  int posX_;
  int posY_;
  bool *actlStPtr_ = actualState_;
  bool *nxtStPtr_ = nextState_;
  
  // Play Game of Life.
  void play();
};
