/**
 * sudoku tree
 */

int getBoardVal(sudokuBoard) 
{
    return sudokuBoard->value;
}

void freeBoard(sudokuBoard)
{
    if(sudokuBoard == NULL)
    {
        return;
    }

    free(sudokuBoard->board);
    free(sudokuBoard);
}

sudokuBoard copyBoard(sudokuBoard)
{
    char newBoard[100][100];
    for(int i = 0 ; i < sudokuBoard->size; ++i)
    {
        for(int j = 0; j < sudokuBoard->size; ++j)
        {
            newBoard[i][j] = sudokuBoard[i][j];
        }
    }
    
    //TODO: malloc struct
}
