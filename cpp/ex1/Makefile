CC=g++
LDLIBS=-lm
CFLAGS= -Wextra -Wall -Wvla -pthread -g -std=c++17 
TARFLAGS= -cvf
#TARARGS=README Makefile Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp

all: ConvexHull PointSetBinaryOperations
	./PointSetBinaryOperations

tar: README Makefile Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp
	tar $(TARFLAGS) ex1.tar README Makefile Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp

PointSet.o: PointSet.h PointSet.cpp
	$(CC) $(CFLAGS) -c PointSet.cpp

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

PointSetBinaryOperations: PointSetBinaryOperations.cpp
	$(CC) $(cflags) PointSetBinaryOperations.cpp -o PointSetBinaryOperations

ConvexHull: Point.o PointSet.o ConvexHull.cpp
	$(CC) $(cflags) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

valgrind: ConvexHull
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ConvexHull

# should it remove tar, and exec too?
clean:
	rm -f *.o *.a
