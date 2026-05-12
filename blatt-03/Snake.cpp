#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

// ___________________________________________________________________________
int dim_x;
int dim_y;
int pos_x;
int pos_y;
int dir_pxl;

// ___________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  dim_x = COLS;
  dim_y = LINES;
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

// ___________________________________________________________________________
void initGame() {
  pos_x = dim_x / 2;
  pos_y = dim_y / 2;
  dir_pxl = KEY_RIGHT;
}

// ___________________________________________________________________________
void drawPixel(int row, int column, int color) {
  attron(COLOR_PAIR(color));
  attron(A_REVERSE);
  mvprintw(row, column * 2, "  ");
  attroff(A_REVERSE);
  attroff(COLOR_PAIR(color));
}

// ___________________________________________________________________________
void drawBorder(int color) {
  for (int i = 0; i < dim_x; ++i) {
    drawPixel(0, i, color);
    drawPixel(dim_y - 1, i, color);
  }

  for (int j = 0; j < dim_y; ++j) {
    drawPixel(j, 0, color);
    drawPixel(j, dim_x - 1, color);
  }
}

// ___________________________________________________________________________
void drawSnake(int color) { drawPixel(pos_y, pos_x, color); }
// ___________________________________________________________________________
bool collidesWithBorder() {
  bool collision = false;
  if (pos_x <= 0 || pos_x >= dim_x - 1) {
    collision = true;
  } else if (pos_y <= 0 || pos_y >= dim_y - 1) {
    collision = true;
  }
  return collision;
}

// ___________________________________________________________________________
void moveSnake() {
  switch (dir_pxl) {
  case KEY_UP:
    pos_y -= 1;
    break;
  case KEY_DOWN:
    pos_y += 1;
    break;
  case KEY_RIGHT:
    pos_x += 1;
    break;
  case KEY_LEFT:
    pos_x -= 1;
    break;
  }
}

// ___________________________________________________________________________
bool handleKey(int key) {
  if (key == 27) {
    return true;
  } else if (key == KEY_UP && dir_pxl != KEY_DOWN) {
    dir_pxl = KEY_UP;
  } else if (key == KEY_DOWN && dir_pxl != KEY_UP) {
    dir_pxl = KEY_DOWN;
  } else if (key == KEY_LEFT && dir_pxl != KEY_RIGHT) {
    dir_pxl = KEY_LEFT;
  } else if (key == KEY_RIGHT && dir_pxl != KEY_LEFT) {
    dir_pxl = KEY_RIGHT;
  }
  return false;
}
