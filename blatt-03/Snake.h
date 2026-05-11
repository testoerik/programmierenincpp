#include <ncurses.h>

// Dimensions of the
extern int dim_x;
extern int dim_y;

// Current position of the Pixel
extern int pos_x;
extern int pos_y;

// Direction
extern int dir_pxl;

void init_Terminal();

void init_Game();

void drawPixel(int row, int column, int color);

void drawBorder(int color);

void drawSnake(int color);

bool collidesWithBorder();

void moveSnake;

bool handleKey(int key);


