.SUFFIXES:
.PHONY: all compile checkstyle test clean

all: clean compile test checkstyle

NcursesDemo.o: Snake.cpp Snake.h
	clang++ -c Snake.cpp

# NcursesDemoMain.o: Snake.cpp Snake.h
# 	clang++ -c Snake.cpp
# 
# NcursesDemoTest.o: Snake.cpp Snake.h
# 	clang++ -c Snake.cpp
# 
# NcursesDemoMain: NcursesDemoMain.o NcursesDemo.o
# 	clang++ -o NcursesDemoMain NcursesDemoMain.o NcursesDemo.o -lncurses
# 
# NcursesDemoTest: NcursesDemoTest.o NcursesDemo.o
# 	clang++ -o NcursesDemoTest NcursesDemoTest.o NcursesDemo.o -lgtest -lgtest_main -lncurses
# 
#  compile:
 
checkstyle:
	clang-format-18 Snake.cpp --dry-run -Werror
format:
	clang-format-18 -i Snake.cpp

test: SnakeTest
 	./SnakeTest
clean:
	rm -f ./NcursesDemoMain ./NcursesDemoTest *.o
