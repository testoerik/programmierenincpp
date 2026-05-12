.SUFFIXES:
.PHONY: all compile checkstyle test clean

all: clean compile test checkstyle

Snake.o: Snake.cpp Snake.h
	clang++ -c Snake.cpp

SnakeMain.o: Snake.cpp Snake.h
 	clang++ -c Snake.cpp
 
SnakeTest.o: Snake.cpp Snake.h
 	clang++ -c Snake.cpp
 
SnakeMain: SnakeMain.o SnakeDemo.o
 	clang++ -o SnakeMain SnakeMain.o SnakeDemo.o -lncurses
 
SnakeTest: SnakeTest.o Snake.o
 	clang++ -o SnakeTest SnakeTest.o Snake.o -lgtest -lgtest_main -lncurses
 
compile:
 
checkstyle:
	clang-format-18 Snake.cpp --dry-run -Werror
format:
	clang-format-18 -i Snake.cpp

test: SnakeTest
 	./SnakeTest
clean:
	rm -f ./SnakeMain ./SnakeDemoTest *.o
