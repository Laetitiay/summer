CC=g++
LDLIBS=-lm
CFLAGS= -Wextra -DNDEBUG -Wall -g -Wvla -pthread -std=c++17 
TARFLAGS= -cvf
TARARGS=README Makefile Matrix.hpp

all: GenericMatrixDriver

tar: $(TARARGS)
	tar $(TARFLAGS) ex3.tar $(TARARGS)

Complex.o: Complex.cpp
	$(CC) $(CFLAGS) -c Complex.cpp

Matrix: Matrix.hpp
	$(CC) $(CFLAGS) -c Matrix.hpp

GenericMatrixDriver: Matrix.hpp GenericMatrixDriver.cpp Complex.o
	$(CC) $(CFLAGS) Matrix.hpp GenericMatrixDriver.cpp Complex.o -o GenericMatrixDriver


clean:
	rm -f *.o Matrix.hpp.gch ex3.tar GenericMatrixDriver Complex.o
