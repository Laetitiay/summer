/**
 * Solves sudoku.
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "SudokuTree.h"
#include <math.h>

#define TOKEN_BUFFER_SIZE 5
#define TABLE_LINE_MAX_SIZE 305
#define NUMBERS_BASE 10
#define EXPECTED_ARGS_NUM 2
#define SUDOKU_TABLE_DELIMETER " "
#define SUDOKU_MAX_SIZE 100
#define SUDOKU_MIN_SIZE 1

#define MSG_INVALID_FILE "Invalid file."
#define MSG_INVALID_ARGS_AMOUNT "Invalid amount of arguments."
#define MSG_IO_ERROR "Could not open file."
#define MSG_NO_SOLUTION "No solution."

/**
 * errors for the input
 */
typedef enum IO_ERROR
{
    err_invalid_number = -1,
    err_no_err = 0,
    err_invalid_args_num = 1,
    err_io_error = 2,
    err_invalid_file = 3,
    err_memory_error = 4
} io_error;


/**
 * Prints the board to stdou
 * @param sudoku  sudokuBoard to print
 */
void printBoard(sudokuBoard* sudoku)
{
    printf("%d\n", sudoku->size);
    for (unsigned i = 0; i < sudoku->size ; ++i)
    {
        for (unsigned j = 0; j < sudoku->size; ++j)
        {
            printf("%d" , sudoku->board[i][j]);
            if(j != sudoku->size - 1)
            {
                printf(SUDOKU_TABLE_DELIMETER);
            }
        }
        printf("\n");
    }
}


/**
 * check for the size of the board
 * @param file file to read from
 * @return Sudoku size
 */
unsigned int getSizeFromFile(FILE *const file)
{
    char *leftovers;
    char buffer[TOKEN_BUFFER_SIZE];

    if(!fgets(buffer, TOKEN_BUFFER_SIZE, file))
    {
        return 0;
    }

    long result = strtol(buffer, &leftovers, NUMBERS_BASE);
    if (result <= SUDOKU_MAX_SIZE && result >= SUDOKU_MIN_SIZE)
    {
        return (unsigned int) result;
    }

    return 0;
}

/**
 * Parses a string to a number
 * @param str  string to parse
 * @param max_size  maximum valid number
 * @return number if is good -1 if not.
 */
int parseNumber(char* str, unsigned max_size)
{
   if (str == NULL) // invalid input
   {
       return err_invalid_number;
   }

    char* leftovers = NULL;
    long num = strtol(str, &leftovers, NUMBERS_BASE);

    if (*str == *leftovers)
    {
        return err_invalid_number;  // error
    }

    if ( 0 <= num && num <= max_size)
    {
        return (int)num;
    }

    return err_invalid_number; // TODO: err
}

/**
 * Generates a sudoku board from a file and a size.
 * @param input input file
 * @param size size of the sudoku
 * @return sudoku board with the values from the file. NULL if something went wrong.
 */
io_error getSudokuBoardFromFile(FILE* input, sudokuBoard* sudoku)
{
    unsigned value = 0;
    char line_buffer[TABLE_LINE_MAX_SIZE];
    char* token_buffer;
    int  number_buffer;

    for (unsigned i = 0; i < sudoku->size; ++i)
    {
        if(!fgets(line_buffer, TABLE_LINE_MAX_SIZE, input))
        {
            return err_io_error;
        }

        token_buffer = strtok(line_buffer, SUDOKU_TABLE_DELIMETER);
        for (unsigned j = 0; j < sudoku->size; ++j)
        {
            number_buffer = parseNumber(token_buffer, sudoku->size);
            if(number_buffer != err_invalid_number)
            {
                sudoku->board[i][j] = (char)number_buffer;
                if(number_buffer != 0)
                {
                    if(!checkIfNumberFitsInBoard(sudoku, i, j, (char)number_buffer))
                    {
                        value++;
                    }
                    else
                    {
                        return err_invalid_file;
                    }
                }
            }
            else
            {
                return err_invalid_file;
            }

            token_buffer = strtok(NULL, SUDOKU_TABLE_DELIMETER);
        }

        if(token_buffer)
        {
            return err_io_error;
        }
    }

    if(fgets(line_buffer, TABLE_LINE_MAX_SIZE, input))
    {
        return err_io_error;
    }

    sudoku->value = value;
    return err_no_err;
}

/**
 * Processes the input file
 * @param input file to process
 * @return input errors
 */
io_error processFile(FILE* input)
{
    unsigned sudoku_size = getSizeFromFile(input);
    unsigned sizeroot = (unsigned)sqrtl(sudoku_size);
    if(!sudoku_size || (sizeroot) * (sizeroot) != sudoku_size)
    {
        return err_invalid_file;
    }

    sudokuBoard* sudoku = (sudokuBoard*)malloc(sizeof(sudoku));
    if(sudoku == NULL)
    {
        return err_memory_error;
    }

    sudoku->size = sudoku_size;
    sudoku->sizeroot = sizeroot;

    io_error board_generating_err = getSudokuBoardFromFile(input, sudoku);
    if (board_generating_err)
    {
        free(sudoku);
        return board_generating_err;
    }

    unsigned best_value = (sudoku_size * sudoku_size);
    sudokuBoard* solution = getBest(sudoku, getBoardChildren, getBoardVal, freeBoard, copyBoard,
                                    best_value);

    if(solution == NULL || solution->value != best_value)
    {
        printf(MSG_NO_SOLUTION);
    }
    else
    {
        printBoard(solution);
    }

    free(sudoku);
    free(solution);
    return err_no_err;
}

/**
 * main method for sudoku solver
 * @param argc argument count should be 2
 * @param argv second arg should be file of sudoku
 * @return input errors
 */
int main(int argc, char *argv[])
{
    if(argc != EXPECTED_ARGS_NUM)
    {
        printf("%s", MSG_INVALID_ARGS_AMOUNT);
        return err_invalid_args_num;
    }

    FILE *input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("%s", MSG_IO_ERROR);
        return err_io_error;

    }

    io_error err = processFile(input);
    if(err == err_invalid_file)
    {
        printf("%s" , MSG_INVALID_FILE);
    }

    fclose(input);
    return err;
}