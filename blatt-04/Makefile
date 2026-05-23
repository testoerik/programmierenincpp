.SUFFIXES:
.PHONY: all compile checkstyle test clean
.PRECIOUS: %.o

CXX = clang++

all: clean compile test checkstyle

%.o: %.cpp GameOfLife.h
	$(CXX) -o $@ -c $<

%Main: %Main.o GameOfLife.o
	$(CXX) -o $@ $^ -lncurses

compile: GameOfLifeMain

checkstyle:
	clang-format-18 *.cpp --dry-run -Werror
format:
	clang-format-18 -i *.cpp

clean:
	rm -f *.o *Main *Test 
