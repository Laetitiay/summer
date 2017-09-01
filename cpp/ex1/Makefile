CC=g++
LDLIBS=-lm
CFLAGS= -Wextra -g -Wall -Wvla -std=cpp17 

all: SudokuSolver libGenericDFS.a

tar: README Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp
	tar -cvf ex1.tar Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp

SudokuSolver: SudokuTree.o libGenericDFS.a  SudokuSolver.o
	$(CC) SudokuSolver.o SudokuTree.o -o SudokuSolver -L. $(LDLIBS)

libGenericDFS.a: GenericDFS.o
	ar -rcs libGenericDFS.a GenericDFS.o

SudokuTree.o: SudokuTree.c SudokuTree.h
	$(CC) $(CFLAGS) -c SudokuTree.c

SudokuSolver.o: SudokuSolver.c
	$(CC) $(CFLAGS) -c SudokuSolver.c

Valgrind: SudokuSolver
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes SudokuSolver tests_cases/s2
clean:
	rm -f *.o *.a
