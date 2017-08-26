typedef struct {
    short size;
    short value;
    char** board;
} sudokuBoard ;

/*
 * TODO: count all the possible insertions of a single digit to
 * the board and put them in the array.
 */
int getBoardChildren(sudokuBoard, sudokuBoard**);
/*
 * TODO: How many empty places are there
 * n^2 - number of zeros
 */
int getBoardVal(sudokuBoard);


/*
 * TODO: fee double array
 */
void freeBoard();

/*
 * copies a board
 */
sudokuBoard copyBoard(sudokuBoard);

