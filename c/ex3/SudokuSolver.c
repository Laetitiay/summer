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

#define MSG_INVALID_ARGS_AMOUNT "Invalid amount of arguments."
#define MSG_IO_ERROR "Could not open file."


typedef enum IO_ERROR {
    err_invalid_number = -1,
    err_no_err = 0,
    err_invalid_args_num = 1,
    err_io_error = 2,
    err_invalid_file = 3,
    err_memory_error =4
} io_error;


void printBoard(sudokuBoard* sudoku)
{
    for (int i = 0; i < sudoku->size ; ++i)
    {
        for (int j = 0; j < sudoku->size; ++j)
        {
            printf("%d" , sudoku->board[i][j]);
            if(j != sudoku->size - 1)
            {
                printf(" ");
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

sudokuBoard* getSudokuBoardFromFile(FILE* input, unsigned size)
{
    sudokuBoard* sudoku = malloc(sizeof(sudokuBoard));
    if(sudoku == NULL) // malloc failed?
    {
        return NULL;
    }

    return sudoku;
}

int parseNumber(char* str, unsigned max_size)
{
   if (str == NULL) // invalid input
   {
       return err_invalid_number;
   }

    char* leftovers = NULL;
    long num = strtol(str, &leftovers, NUMBERS_BASE);

    if (!leftovers)
    {
        return err_invalid_number;  // error
    }

    if ( 0 <= num && num <= max_size)
    {
        return (int)num;
    }

    return err_invalid_number; // TODO: err
}

io_error processFile(FILE* input)
{
    unsigned sudoku_size = getSizeFromFile(input);
    if(!sudoku_size)
    {
        return err_invalid_file;
    }

    sudokuBoard* sudoku = malloc(sizeof(sudoku));
    if(sudoku == NULL)
    {
        return err_memory_error;
    }
    sudoku->size = sudoku_size;
    sudoku->sizeroot = (unsigned)sqrtl(sudoku_size);
    unsigned value = 0;


    char line_buffer[TABLE_LINE_MAX_SIZE];
    char* token_buffer;
    int  number_buffer;

    for (unsigned i = 0; i < sudoku_size; ++i) {
        if(!fgets(line_buffer, TABLE_LINE_MAX_SIZE, input))
        {
            return err_io_error;
        }

        token_buffer = strtok(line_buffer, SUDOKU_TABLE_DELIMETER);
        for (int j = 0; j < sudoku_size; ++j)
        {
            number_buffer = parseNumber(token_buffer, sudoku_size);
            // TODO: error
            if(number_buffer != err_invalid_number)
            {
                sudoku->board[i][j] = (char)number_buffer;
                if(number_buffer != 0)
                {
                    value++;
                }
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

    //printBoard(sudoku);

    sudokuBoard* solution = getBest(sudoku, getBoardChildren, getBoardVal, freeBoard, copyBoard,
                                    (sudoku_size * sudoku_size));

    if(solution == NULL)
    {
        printf("No solution");
    }
    else
    {
        printBoard(solution);
    }

    return err_no_err;
}

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
    fclose(input);
    return err;
}