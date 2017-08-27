#ifndef SUDOKUTREE_H
#define SUDOKUTREE_H

#include "GenericDFS.h"
#include <stdlib.h>

typedef struct SudokuBoards{
    short size;
    unsigned value;
    short sizeroot;
    char board[100][100];
} sudokuBoard ;

typedef enum {
    does_not_fit = 0,
    fits = 1

} sudokuFits;

/*
 * TODO: count all the possible insertions of a single digit to
 * the board and put them in the array.
 */
int getBoardChildren(pNode node,pNode** array);
/*
 * TODO: How many empty places are there
 * n^2 - number of zeros
 */
int getBoardVal(pNode board);


/*
 * TODO: fee double array
 */
void freeBoard(pNode node);

/*
 * copies a board
 */
pNode copyBoard(pNode node);

#endif
