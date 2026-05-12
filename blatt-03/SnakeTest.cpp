#include "Snake.h"
#include <gtest/gtest.h>

int KEY_DOWN = 258;
int KEY_UP = 259;
int KEY_LEFT = 260;
int KEY_RIGHT = 261;

TEST(SnakeTest, initGame) {
	int dim_x = 20;
	int dim_y = 20;
	initGame();
	EXPECT_EQUAL(dim_x, 10);
	EXPECT_EQUAL(dim_y, 10);
	EXPECT_EQUAL(dir_pxl, KEY_RIGHT);
	}

Test(SnakeTest, collidesWithBorder) {
	int dim_x = 20;
	int dim_y = 20;
	pos_x = 0;
	pos_y = 9;
	EXPECT_TRUE(collidesWithBorder());
	}

TEST(SnakeTest, moveSnake) {
	pos_x = 10;
	pos_y = 10;
	dir_pxl = KEY_UP;
	EXPECT_EQUAL(pos_y, 9);
	}

TEST(SnakeTest, handleKey) {
	EXPECT_TRUE(handleKey(27);
	
	dir_pxl = KEY_RIGHT;
	EXPECT_FALSE(handleKey(KEY_LEFT);
	EXPECT_EQUAL(dir_pxl, KEY_RIGHT);
	}	

