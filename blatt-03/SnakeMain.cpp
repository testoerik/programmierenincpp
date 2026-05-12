#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  initTerminal();
  initGame();
  double speed = 5.0;
  double acceleration = 0.5;
  
  clear();
  drawBorder(1);
  drawSnake(2);
  refresh();

  while (true) {
    int key = getch();
    if (key != ERR) {
	if (handleKey(key)) {
		break;
	}
    }	
    }
  }
}
