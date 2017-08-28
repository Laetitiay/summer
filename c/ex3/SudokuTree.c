#include "SudokuTree.h"

/**
 * returns the sudoku board's value. Value is how many spots are taken.
 * @param board board to get value from
 * @return value of the board
 */
unsigned getBoardVal(pNode board)
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

    //free(sudoku_board->board);
    free(sudoku_board);
}

pNode copyBoard(pNode node)
{
    sudokuBoard* toCopy = (sudokuBoard*)node;

    sudokuBoard* newSudoku = (sudokuBoard*)malloc(sizeof(sudokuBoard));
    if(!newSudoku)
    {
        return NULL;
    }
    newSudoku->size = toCopy->size;
    newSudoku->value = toCopy->value;
    newSudoku->sizeroot = toCopy->sizeroot;
    for(unsigned i = 0 ; i < toCopy->size; ++i)
    {
        for(unsigned j = 0; j < toCopy->size; ++j)
        {
            newSudoku->board[i][j] = toCopy->board[i][j];
        }
    }

    return newSudoku;
}

sudokuFits findNearestZero(const sudokuBoard* const sudoku, point *board_point)
{
    for (unsigned i = 0; i < sudoku->size ; ++i)
    {
        for (unsigned j = 0; j < sudoku-> size ; ++j)
        {
            if(sudoku->board[i][j] == 0)
            {
                board_point->row = i;
                board_point->column = j;
                return fits;
            }
        }
    }
    return does_not_fit;
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
    unsigned startRow = (row / sudoku->sizeroot) * sudoku->sizeroot;
    unsigned startCol = (column / sudoku->sizeroot) * sudoku->sizeroot;

    for (unsigned i = startRow; i < startRow + sudoku->sizeroot ; ++i)
    {
        for (unsigned j = startCol; j < startCol + sudoku->sizeroot ; ++j)
        {
            if(sudoku->board[i][j] == number)
            {
                return does_not_fit;
            }
        }
    }
    return fits;
}


sudokuFits checkIfNumberFitsInBoard(sudokuBoard* sudoku, unsigned row, unsigned column, char number)
{
    if(checkRowAndColumn(sudoku, row, column, number) == does_not_fit)
    {
        return does_not_fit;
    }
    return checkBox(sudoku, row, column, number);
}

char* possibleSudokuValues(sudokuBoard* sudoku, unsigned row, unsigned column)
{
    assert(sudoku->size <= 100);
    char* possibleValues = malloc(sizeof(char) * (sudoku->size));
    if (!possibleValues) // malloc failed
    {
        return NULL;
    }
    for(unsigned i = 0; i < sudoku->size ; ++i)
    {
        if(checkIfNumberFitsInBoard(sudoku, row, column, (char)(i + 1)))
        {
            possibleValues[i] = (char) (i+1);
        }
        else
        {
            possibleValues[i] = 0;
        }
    }
    return possibleValues;
}

int getBoardChildren(pNode node, pNode** arr)
{
    sudokuBoard* my_board = (sudokuBoard*)node;
    sudokuBoard** children = (sudokuBoard**)malloc(sizeof(sudokuBoard) * my_board->size ); // maximum children amount
    point* board_point = malloc(sizeof(point));
    if (!children || !board_point) // malloc failed
    {
        free(children);
        free(board_point);
        return 0;
    }
    char* possibleValues;
    int number_of_childern = 0;

    if (!findNearestZero(my_board, board_point)) // no children!!!!
    {
        return 0;
    }

    possibleValues = possibleSudokuValues(my_board, board_point->row, board_point->column);
    for (unsigned i = 0; i < my_board->size ; ++i)
    {
        if (possibleValues[i] != 0)
        {
            children[number_of_childern] = copyBoard(node);
            children[number_of_childern]->board[board_point->row][board_point->column] = possibleValues[i];
            children[number_of_childern]->value++;
            number_of_childern++;
        }
    }

    free(possibleValues);
    free(board_point);
    *arr = (pNode *) children;
    return number_of_childern;
}

