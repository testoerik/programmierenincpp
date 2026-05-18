// Created by eh295

#include <ncurses.h>
#include <unistd>

extern bool actualState[];
extern bool nextState[];

int *a = actualState;
int *n = nextState;

extern int x;
extern int y;

extern int numSteps;
extern int numAliveCells;

extern bool StateGame;

const int MAX_NUM_CELLS;


// Initialize the terminal for use with ncurses commands.
void initTerminal();
void initGame();

void ShowState();

int numAliveNeighboors(int row, int col);

void updateState();

bool processUserInput(int keycode);


