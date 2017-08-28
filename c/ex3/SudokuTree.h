#ifndef SUDOKUTREE_H
#define SUDOKUTREE_H

#include "GenericDFS.h"
#include <stdlib.h>
#include <assert.h>

typedef struct SudokuBoards{
    unsigned size;
    unsigned value;
    unsigned sizeroot;
    char board[100][100];
} sudokuBoard ;

typedef struct Point {
    unsigned row;
    unsigned column;
} point;
typedef enum {
    does_not_fit = 0,
    fits = 1

} sudokuFits;

int getBoardChildren(pNode node,pNode** array);
unsigned int getBoardVal(pNode board);
void freeBoard(pNode node);
pNode copyBoard(pNode node);

#endif
