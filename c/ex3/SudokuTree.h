#ifndef SUDOKUTREE_H
#define SUDOKUTREE_H

#include "GenericDFS.h"
#include <stdlib.h>
#include <assert.h>

/**
 * Sudoku Board Struct
 */
typedef struct SudokuBoards
{
    unsigned size;
    unsigned value;
    unsigned sizeroot;
    char board[100][100];
} sudokuBoard ;

/**
 * Point in the board struct
 */
typedef struct Point
{
    unsigned row;
    unsigned column;
} point;
/**
 * Fits in the board enum
 */
typedef enum
{
    does_not_fit = 0,
    fits = 1

} sudokuFits;

/**
 * generates the children of the board
 * @param node board to make children of
 * @param arr array to put the children in
 * @return number of children
 */
int getBoardChildren(pNode node, pNode** array);


/**
 * returns the sudoku board's value. Value is how many spots are taken.
 * @param board board to get value from
 * @return value of the board
 */
unsigned int getBoardVal(pNode board);


/**
 * frees the node memory
 * @param node node to ree
 */
void freeBoard(pNode node);


/**
 * copies the board
 * @param node board to copy
 * @return copy of the board
 */
pNode copyBoard(pNode node);

/**
 * Checks if a number fits in the spot
 * @param sudoku soduku to check in
 * @param row row to check in
 * @param column column to check in
 * @param number  number to check if valid
 * @return if it fits or not
 */
sudokuFits checkIfNumberFitsInBoard(sudokuBoard* sudoku, unsigned row, unsigned column, char number);
#endif
