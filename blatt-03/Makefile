.SUFFIXES:
.PHONY: all compile checkstyle format test clean

CXX = clang++

all: compile test checkstyle

compile: SnakeMain 

%.o: %.cpp Snake.h
		$(CXX) -o $@ -c $<

%Main: %.o Snake.o
	$(CXX) -o SnakeMain SnakeMain.cpp Snake.o -lncurses

checkstyle:
	clang-format-18 *.cpp *.h --dry-run -Werror

format:
	clang-format-18 -i *.cpp *.h

clean:
	rm -f SnakeMain  Snake.o SnakeMain.o .o
