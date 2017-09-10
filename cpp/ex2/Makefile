CC=g++
LDLIBS=-lm
CFLAGS= -Wextra -DNDEBUG -Wall -g -Wvla -pthread -std=c++17 
TARFLAGS= -cvf
TARARGS=README Makefile Point.cpp PrintOuts.cpp Shape.cpp ShapeFactory.cpp Shapes.cpp Trapezoid.cpp\
	   	Triangle.cpp Defs.h Point.h PrintOuts.h ShapeFactory.h Shape.h Trapezoid.h Triangle.h

all: Shapes

tar: $(TARARGS)
	tar $(TARFLAGS) ex2.tar $(TARARGS)

Shape.o: Shape.h Shape.cpp
	$(CC) $(CFLAGS) -c Shape.cpp

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

Triangle.o: Triangle.h Triangle.cpp
	$(CC) $(CFLAGS) -c Triangle.cpp

Trapezoid.o: Trapezoid.h Trapezoid.cpp
	$(CC) $(CFLAGS) -c Trapezoid.cpp

PrintOuts.o: PrintOuts.cpp PrintOuts.h
	$(CC) $(CFLAGS) -c PrintOuts.cpp

ShapeFactory.o: ShapeFactory.cpp
	$(CC) $(CFLAGS) -c ShapeFactory.cpp

Shapes: Point.o Shape.o Trapezoid.o Triangle.o Shapes.o PrintOuts.o ShapeFactory.o Defs.h
	$(CC) -g Point.o Shape.o Trapezoid.o Triangle.o Shapes.o PrintOuts.o ShapeFactory.o -o Shapes

valgrind: Shapes
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes Shapes test_examples/input5.in

clean:
	rm -f *.o Shapes ex2.tar
