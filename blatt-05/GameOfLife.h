// Created by eh295

#pragma once
#include "./TerminalManager.h"

class GameOfLife {
private:
  // Current position of each cell.
  int posX_;
  int posY_;

  static const int MAX_NUM_CELLS = 10'000;

  bool actualState_[MAX_NUM_CELLS];
  bool nextState_[MAX_NUM_CELLS];

  bool *actlStPtr_;
  bool *nxtStPtr_;
  // State of the game: Is it playing (true) or paused (paused) ?
  bool stateGame_;
  // TerminalManager for rendering our game.
  TerminalManager *terminalManager_;

public:
  // Constructor
  GameOfLife(TerminalManager *terminalManager);
  // Play Game of Life.
  void play();

private:
  // Show the state of each cell in the terminal.
  void showState();
  // In this void function are the game of life rules.
  void updateState();

  int numAliveNeighbors(int row, int col);

  // Handles all the possible user inputs, for example space key for pause or
  // playing, 'q' for quit etc.
  bool processUserInput(UserInput userInput);
};
