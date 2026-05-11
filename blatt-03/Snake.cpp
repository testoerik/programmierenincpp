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
void init_Terminal() {
  initscr();
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  dim_x = LINES;
  dim_y = COLS;
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

// ___________________________________________________________________________
void init_Game() {
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
  for (int i = 0; i < dim_x, ++i) {
    drawPixel(0, i, color);
    drawPixel(dim_x, i, color);
  }

  for (int j = 0, j < dim_y, ++j) {
    drawPixel(j, 0 color);
    drawPixel(j, dim_y, color);
  }
}

// ___________________________________________________________________________
void drawSnake() {
	drawPixel(pos_y, pos_x, color);

// ___________________________________________________________________________
bool collidesWithBorder() {
	case pos_x = 1;
		return False;
  	case pos_y = 1;
		return False;
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
    pos_x += 2;
    break;
  case Key_LEFT:
    pos_x -= 2;
    break;
  }
}

// ___________________________________________________________________________
bool handleKey() {
}
