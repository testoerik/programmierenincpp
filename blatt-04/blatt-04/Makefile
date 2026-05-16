.SUFFIXES:
.PHONY: all compile checkstyle test clean
.PRECIOUS: %.o

CXX = clang++

all: clean compile test checkstyle

%.o: %.cpp NcursesDemo.h
	$(CXX) -o $@ -c $<

%Main: %Main.o NcursesDemo.o
	$(CXX) -o $@ $^ -lncurses

compile: NcursesDemoMain

checkstyle:
	clang-format-18 *.cpp --dry-run -Werror
format:
	clang-format-18 -i *.cpp

clean:
	rm -f *.o *Main *Test 
