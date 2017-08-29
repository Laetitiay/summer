CC = gcc
CFLAGS = -Wall -Wextra -Wvla -c -g -std=c99 -DNDEBUG	
DEPS_LINE_SEPARATOR = LineSeparator.c LineSeparator.h
DEPS_MY_STRING = MyString.c MyString.h



MyStringExample: $(DEPS_MY_STRING)
	$(CC) $(CFLAGS) MyString.c -o MyStringExample

LineSeparator: $(DEPS_LINE_SEPARATOR)
	$(CC) $(CFLAGS) LineSeparator.c -o LineSeparator 

LineSeparator.o: $(DEPS_LINE_SEPARATOR)
	$(CC) $(CFLAGS) -c LineSeparator.c

MyString.o: $(DEPS_MY_STRING)
	$(CC) $(CFLAGS) -c MyString.c

clean:
	-rm -f *.o MyStringExample LineSeparator 
	
