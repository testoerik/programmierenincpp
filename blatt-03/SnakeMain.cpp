#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
	startNcurses();
	initTerminal();
	initGame();
	drawBorder();
	drawSnake();
	while (true) ;
		}
