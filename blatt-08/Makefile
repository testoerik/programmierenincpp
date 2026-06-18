.PHONY: all compile checkstyle test clean format
.PRECIOUS: %.o
.SUFFIXES:

all: format compile test

compile: RingBufferTest

checkstyle:
	clang-format-18 --dry-run -Werror *.h *.cpp

format:
	clang-format-18 -i *.h *.cpp

test: RingBufferTest
	./RingBufferTest

clean:
	rm -f RingBufferTest
	rm -f *.o

%.o: %.cpp *.h
	clang++ -c $< -o $@

RingBufferTest: RingBufferTest.o RingBuffer.o
	clang++ -g -fsanitize=address -o RingBufferTest $^ -lgtest -lgtest_main
