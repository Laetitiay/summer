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

typedef enum IO_ERRORS
{
    err_no_err = 0,
    err_no_input_file = 1,
    err_invalid_input = 2,
} io_error;

typedef enum INPUT_STATE
{
    i_xpos = 1,
    i_ypos = 2,
    i_x_velocity = 3,
    i_y_velocity = 4,
    i_time = 5,
    i_total_steps= 6,
    i_show_steps = 7,
    i_end = 8,
} input_state;

long double xpos,ypos,x_velocity,y_velocity,time,step_size;
long total_steps, show_steps;
long double d1();
long double d2();
long double accelerateX();
long double accelerateY();
void singleMove();
void arenstorfRoute(char *);

/**
 *
 * @return
 */
long double d1() {
    return powl(powl(xpos + ALPHA, 2) + powl(ypos, 2), (1.5));
}

/**
 *
 * @return
 */
long double d2() {
    return powl(powl(xpos - BETA, 2) + powl(ypos, 2), (1.5));
}

/**
 *
 * @return
 */
long double accelerateX() {
    return xpos + (2 * y_velocity) - BETA * (xpos + ALPHA)/d1() - ALPHA * (xpos - BETA)/d2();
}

/**
 *
 * @return
 */
long double accelerateY() {
    return ypos - (2 * x_velocity) - BETA * (ypos)/d1() - ALPHA * (ypos)/d2();
}

/**
 *
 */
void singleMove() {
    // tmp
    long double next_xpos;
    long double next_ypos;
    long double next_x_velocity;
    long double next_y_velocity;
    next_xpos = xpos + x_velocity * step_size;
    next_ypos = ypos + y_velocity * step_size;
    next_x_velocity = x_velocity + accelerateX() * step_size;
    next_y_velocity = y_velocity + accelerateY() * step_size;
    xpos = next_xpos;
    ypos = next_ypos;
    x_velocity = next_x_velocity;
    y_velocity = next_y_velocity;
    return;
}

/**
 *
 */
void arenstorfRoute(char *outFile) {
    //TODO: will it always succeed?
    FILE *outputFile = fopen(outFile, "w");
    for (int i = 0; i < total_steps; ++i)
    {
        singleMove();
        if ( i % (total_steps / show_steps) == 0)
        {
            // TODO: no comma at the end
            fprintf(outputFile, "%.3Le, %.3Le, ",xpos, ypos);
        }
    }
    fclose(outputFile);
}

/**
 * process input
 */
io_error processInput(input_state state, char *in)
{
    char **str = NULL;
    switch(state)
    {
        case(i_xpos):
            xpos = strtold(in,str);
            break;
        case(i_ypos):
            ypos = strtold(in,str);
            break;
        case(i_x_velocity):
            x_velocity = strtold(in,str);
            break;
        case(i_y_velocity):
            y_velocity = strtold(in,str);
            break;
        case(i_time):
            time = strtold(in,str);
            break;
        case(i_total_steps):
            total_steps = strtol(in,str,NUM_BASE);
            break;
        case(i_show_steps):
            show_steps = strtol(in,str,NUM_BASE);
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

io_error getFileInput(char *fileName)
{
    input_state state = i_xpos;
    FILE *inputFile = fopen(fileName, "r");
    char *token = NULL;
    char data[MAX_CHARS_IN_LINE];

    if(inputFile)
    {
        for(int i = 0; i < INPUT_FILE_LINES_NUM ; i++)
        {
            fgets(data, MAX_CHARS_IN_LINE, inputFile);
            token = strtok(data, INPUT_DELIM);
            while(token != NULL)
            {
                if(!processInput(state, token))
                {
                    state++;
                }
                else
                {
                    return err_invalid_input;
                }
                token = strtok(NULL, INPUT_DELIM);
            }
        }
    }
    else
    {
        return err_no_input_file;
    }

    fclose(inputFile);
    if(state == i_end)
    {
        return err_no_err;
    }
    return err_invalid_input;
}

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

io_error getUserInput()
{
    char data[MAX_CHARS_IN_LINE];
    for (input_state state = i_xpos; state < i_end ; state++)
    {
        printUserInputStateMessage(state);
        fgets(data, MAX_CHARS_IN_LINE, stdin);
        processInput(state, data);
    }
    return err_no_err;
}

unsigned checkForLogicalErrors()
{
    if(show_steps > total_steps)
    {
        //error
    }
}

/**
 * main
 */
int main(int argc, char *argv[])
{
    char *output_file;
    if(argc == ARG_NUM_FILE_INPUT)
    {
        if(!getFileInput(argv[1]))
        {

        }
        output_file = argv[2];
    }
    else if (argc == ARG_NUM_STDIN)
    {
        getUserInput();
        output_file = argv[1];
    }
    else
    {
        //TODO: ERROR
        return 1;
    }
    step_size = (time/total_steps);
    arenstorfRoute(output_file);
    return 0;
}

