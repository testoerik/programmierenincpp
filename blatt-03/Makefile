.SUFFIXES:
.PHONY: all compile checkstyle format test clean

CXX = clang++

all: compile test checkstyle

compile: SnakeMain SnakeTest

%.o: %.cpp Snake.h
		$(CXX) -o $@ -c $<

%Main: %.o Snake.o
	$(CXX) -o SnakeMain SnakeMain.cpp Snake.o -lncurses

SnakeTest: SnakeTest.o Snake.o
	$(CXX) SnakeTest.o Snake.o -lgtest -lgtest_main -pthread -lncurses -o SnakeTest

checkstyle:
	clang-format-18 *.cpp *.h --dry-run -Werror

format:
	clang-format-18 -i *.cpp *.h

test: SnakeTest
	./SnakeTest

clean:
	rm -f SnakeMain SnakeTest Snake.o SnakeMain.o SnakeTest.o
