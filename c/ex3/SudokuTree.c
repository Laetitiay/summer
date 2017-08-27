#include "SudokuTree.h"

/**
 * sudoku tree
 */

int getBoardVal(pNode board)
{
    if(board == NULL)
    {
        return 0;
    }
    return ((sudokuBoard*)board)->value;
}

void freeBoard(pNode node)
{
    sudokuBoard* sudoku_board = (sudokuBoard*)node;
    if(sudoku_board == NULL)
    {
        return;
    }

    free(sudoku_board->board);
    free(sudoku_board);
}

pNode copyBoard(pNode node)
{
    sudokuBoard* toCopy = (sudokuBoard*)node;

    sudokuBoard* newSudoku = (sudokuBoard*)malloc(sizeof(sudokuBoard));
    newSudoku->size = toCopy->size;
    newSudoku->value = toCopy->value;
    newSudoku->sizeroot = toCopy->sizeroot;
    for(int i = 0 ; i < toCopy->size; ++i)
    {
        for(int j = 0; j < toCopy->size; ++j)
        {
            newSudoku->board[i][j] = toCopy->board[i][j];
        }
    }

    return newSudoku;
}

int getBoardChildren(pNode node, pNode** arr)
{
    sudokuBoard* my_board = (sudokuBoard*)node;
    sudokuBoard** array = malloc(sizeof(sudokuBoard*) * my_board->size ); // maximum children amount


    *arr = array;
    return 0;
}


/** my functions **/
sudokuFits checkRowAndColumn(sudokuBoard* sudoku, unsigned row, unsigned column, char number)
{
    for(unsigned i = 0; i < sudoku->size ; ++i)
    {
        if(sudoku->board[i][column] == number || sudoku->board[row][i] == number)
        {
            return does_not_fit;
        }
    }

    return fits;
}

sudokuFits checkBox(sudokuBoard* sudoku, unsigned row, unsigned column, char number)
{
    int startRow = (row / sudoku->sizeroot) * sudoku->sizeroot;
    int startCol = (column / sudoku->sizeroot) * sudoku->sizeroot;

    for (int i = startRow; i < startRow + sudoku->sizeroot ; ++i)
    {
        for (int j = startCol; j < startCol + sudoku->sizeroot ; ++j)
        {
            if(sudoku->board[i][j] == number)
            {
                return does_not_fit;
            }
        }

    }

    return fits;
}



