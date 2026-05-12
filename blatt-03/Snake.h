#include <ncurses.h>
#pragma once

extern int dim_x;
extern int dim_y;

extern int pos_x;
extern int pos_y;

extern int dir_pxl;

void initTerminal();

void initGame();

void drawPixel(int row, int column, int color);

void drawBorder(int color);

void drawSnake(int color);

bool collidesWithBorder();

void moveSnake();

bool handleKey(int key);


