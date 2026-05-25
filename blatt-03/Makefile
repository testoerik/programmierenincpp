.SUFFIXES:
.PHONY: all compile checkstyle test clean format

#CXX = clang++ -g
BASENAME = Snake
#OBJS = $(BASENAME).o TerminalManager.o
LIBS = -lncurses
CXX = clang++ -Wall -Wextra -O3 -I/usr/include/freetype2
OBJS = $(BASENAME).o OpenGLTerminalManager.o
LIBS = -lncurses -lglfw -lGL -lX11 -lrt -ldl -lfreetype
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile format checkstyle # test

compile: $(BASENAME)Main 

checkstyle:
	clang-format-18 --dry-run -Werror *.h *.cpp

format:
	clang-format-18 -i *.h *.cpp


test: $(BASENAME)Test
	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)


clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o
