/**
 * @file ex1.c
 * @author liron
 * @section DESCRIPTION
 * This program computes the arenstorf route for the given input.
 * Input  : Can be given by file or stdin.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA 0.012299
#define BETA (1 - ALPHA)
#define NUM_BASE 10
#define INPUT_DELIM ","
#define ARG_NUM_FILE_INPUT 3
#define ARG_NUM_STDIN 2
#define INPUT_FILE_LINES_NUM 2
#define MAX_CHARS_IN_LINE 256
#define MSG_INVALID_NUMBER_OF_ARGS "Invalid number of arguments."
#define MSG_INVALID_INPUT "Invalid input."
#define MSG_SUCCESS "Computed successfully."

// was also used for general errors. Sorry.
typedef enum IO_ERRORS
{
    err_no_err = 0,
    err_no_file = 1,
    err_invalid_input = 2,
} io_error;

typedef enum INPUT_STATE
{
    i_xpos = 1,
    i_ypos = 2,
    i_x_velocity = 3,
    i_y_velocity = 4,
    i_time = 5,
    i_total_steps = 6,
    i_show_steps = 7,
    i_end = 8,
} input_state;

// global variables
long double xpos, ypos, x_velocity, y_velocity, time, step_size;
long total_steps, show_steps;

// functions declarations
long double d1();
long double d2();
long double accelerateX();
long double accelerateY();
void singleMove();
io_error arenstorfRoute(char *);
io_error getFileInput(char *);
io_error processInput(input_state, char *);
io_error getFileInput(char *fileName);
void printUserInputStateMessage(input_state state);
io_error getUserInput();
io_error checkForLogicalErrors();
int main(int argc, char *argv[]);

/**
 * d1 part of the formula.
 * @return d1
 */
long double d1()
{
    return powl(powl(xpos + ALPHA, 2) + powl(ypos, 2), (1.5));
}

/**
 * d2 part of the formula.
 * @return d2
 */
long double d2()
{
    return powl(powl(xpos - BETA, 2) + powl(ypos, 2), (1.5));
}

/**
 * Calculates the acceleraiton of the x pos.
 * @return y pos accelerations
 */
long double accelerateX() 
{
    return xpos + (2 * y_velocity) - BETA * (xpos + ALPHA) / d1() - ALPHA * (xpos - BETA) / d2();
}

/**
 * Calculates the acceleraiton of the y pos.
 * @return y pos accelerations
 */
long double accelerateY()
{
    return ypos - (2 * x_velocity) - BETA * (ypos) / d1() - ALPHA * (ypos) / d2();
}

/**
 * Preforms a single move of the ship using the formulas.
 */
void singleMove()
{
    long double next_xpos;
    long double next_ypos;
    long double next_x_velocity;
    next_xpos = xpos + x_velocity * step_size;
    next_ypos = ypos + y_velocity * step_size;
    next_x_velocity = x_velocity + accelerateX() * step_size;
    y_velocity = y_velocity + accelerateY() * step_size;
    xpos = next_xpos;
    ypos = next_ypos;
    x_velocity = next_x_velocity;
    return;
}

/**
 * Calculates the arenstorf route and writes it to a file.
 * @param outFile  file to write the result to.
 * @return 0 iff succeeded to write. some other io_error otherwise.
 */
io_error arenstorfRoute(char *outFile)
{
    FILE *outputFile = fopen(outFile, "w");
    if (outputFile)
    {
        for (int i = 0; i < total_steps; ++i)
        {
            singleMove();
            // write only relevant steps
            if ( i % (total_steps / show_steps) == 0)
            {
                fprintf(outputFile, "%.3Le, %.3Le", xpos, ypos);
                // add "," iff not at the end
                if(i != total_steps - 1)
                {
                    fprintf(outputFile, ", ");
                }
                else
                {
                    fprintf(outputFile, "\n");
                }
            }
        }
    }
    else
    {
        fclose(outputFile);
        return err_no_file;
    }
    fclose(outputFile);
    return err_no_err;
}

/**
 * Processes a string input according to the recieved state.
 * @param state state of the input
 * @param in string input received
 * @return error if could not process, 0 otherwise.
 */
io_error processInput(input_state state, char *in)
{
    char **str = NULL; // leftover from the input (not a number)
    switch(state)
    {
        case(i_xpos):
            xpos = strtold(in, str);
            break;
        case(i_ypos):
            ypos = strtold(in, str);
            break;
        case(i_x_velocity):
            x_velocity = strtold(in, str);
            break;
        case(i_y_velocity):
            y_velocity = strtold(in, str);
            break;
        case(i_time):
            time = strtold(in, str);
            break;
        case(i_total_steps):
            total_steps = strtol(in, str, NUM_BASE);
            break;
        case(i_show_steps):
            show_steps = strtol(in, str, NUM_BASE);
            break;
        default:
            return err_invalid_input;
    }

    if(str)
    {
        return err_invalid_input;
    }
    return err_no_err;
}

/**
 * Reads the input from a file
 * @param fileName file name to access for the input
 * @return error if could not process the file, 0 otherwise.
 */
io_error getFileInput(char *fileName)
{
    input_state state = i_xpos;
    FILE *inputFile = fopen(fileName, "r");
    char *token = NULL;
    char data[MAX_CHARS_IN_LINE];

    if(!inputFile)
    {
        fclose(inputFile);
        return err_no_file;
    }

    for(int i = 0; i < INPUT_FILE_LINES_NUM ; i++)
    {
        // read one line
        if(!fgets(data, MAX_CHARS_IN_LINE, inputFile))
        {
            fclose(inputFile);
            return err_invalid_input;
        }
        else
        {
            // split it by the delimeter and process each unit.
            token = strtok(data, INPUT_DELIM);
            while(token != NULL)
            {
                if(!processInput(state, token))
                {
                    state++;
                }
                else
                {
                    fclose(inputFile);
                    return err_invalid_input;
                }
                token = strtok(NULL, INPUT_DELIM);
            }
        }
    }

    fclose(inputFile);
    if(state == i_end)
    {
        return err_no_err;
    }

    return err_invalid_input;
}

/**
 * printes an appropriate user message according to the input state.
 * @param state current state
 */
void printUserInputStateMessage(input_state state)
{
    char *message;
    switch(state)
    {
        case(i_xpos):
            message = "Enter initial pos x:\n";
            break;
        case(i_ypos):
            message = "Enter initial pos y:\n";
            break;
        case(i_x_velocity):
            message = "Enter initial vel x:\n";
            break;
        case(i_y_velocity):
            message = "Enter initial vel y:\n";
            break;
        case(i_time):
            message = "Enter total time T:\n";
            break;
        case(i_total_steps):
            message = "Enter num of steps:\n";
            break;
        case(i_show_steps):
            message = "Enter num of steps to save:\n";
            break;
        default:
            return;
    }
    printf("%s", message);
    return;
}

/**
 * read input from the stdin
 * @return error if could not read, 0 otherwise.
 */
io_error getUserInput()
{
    char data[MAX_CHARS_IN_LINE];
    for (input_state state = i_xpos; state < i_end ; state++)
    {
        printUserInputStateMessage(state);
        if(!fgets(data, MAX_CHARS_IN_LINE, stdin))
        {
            return err_no_file;
        }
        processInput(state, data);
    }
    return err_no_err;
}

/**
 * checks for logical errors in the input
 * @return error if found any errors, 0 otherwise.
 */
io_error checkForLogicalErrors()
{
    if(show_steps > total_steps)
    {
        return err_invalid_input;
    }

    if(total_steps % show_steps != 0)
    {
        return err_invalid_input;
    }

    if(!((time > 0) && (total_steps > 0) && (show_steps > 0)))
    {
        return err_invalid_input;
    }
    
    return err_no_err;
}

/**
 * Main method. Runs the program.
 * @param argc amount of arguments
 * @param argv arguments array
 * @return
 */
int main(int argc, char *argv[])
{
    char *output_file;
    // File input
    if(argc == ARG_NUM_FILE_INPUT)
    {
        if(getFileInput(argv[1]))
        {
            printf("%s", MSG_INVALID_INPUT);            
            return err_invalid_input;
        }
        output_file = argv[2];
    } // user input
    else if (argc == ARG_NUM_STDIN)
    {
        if(getUserInput())
        {
            printf("%s", MSG_INVALID_INPUT);            
            return err_invalid_input;
        }
        output_file = argv[1];
    } // invalid # of args
    else
    {
        printf("%s", MSG_INVALID_NUMBER_OF_ARGS);
        return err_invalid_input;
    }

    if(checkForLogicalErrors())
    {
        printf("%s", MSG_INVALID_INPUT);            
        return err_invalid_input;
    }

    step_size = (time / total_steps);
    if(arenstorfRoute(output_file))
    {
        printf("%s", MSG_INVALID_INPUT);            
        return err_invalid_input;
    }
    printf(MSG_SUCCESS);
    return err_no_err;
}

