CC=g++
LDLIBS=-lm
CFLAGS= -Wextra -DNDEBUG -Wall -g -Wvla -pthread -std=c++17 
TARFLAGS= -cvf
TARARGS=README Makefile Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp

all: ConvexHull PointSetBinaryOperations
	./PointSetBinaryOperations

tar: $(TARARGS)
	tar $(TARFLAGS) ex1.tar $(TARARGS)

PointSet.o: PointSet.h PointSet.cpp
	$(CC) $(CFLAGS) -c PointSet.cpp

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

PointSetBinaryOperations: PointSetBinaryOperations.cpp PointSet.o Point.o
	$(CC) $(CFLAGS) PointSet.o Point.o PointSetBinaryOperations.cpp -o PointSetBinaryOperations

ConvexHull: Point.o PointSet.o ConvexHull.cpp
	$(CC) $(CFLAGS) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

valgrind: ConvexHull
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ConvexHull

clean:
	rm -f *.o ConvexHull PointSetBinaryOperations ex1.tar
