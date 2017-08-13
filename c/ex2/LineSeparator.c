#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_CHARS_IN_LINE 400

//is_ stands for input_state_
typedef enum INPUT_STATE
{
    is_dim = 0,
    is_in_lines = 1,
    is_learning = 2,
    is_work = 3
} input_state;

typedef enum IO_ERRORS
{
    err_no_err = 0,
    err_no_file = 1,
    err_invalid_input = 2,
} io_error;

typedef struct Vectors {
    double *cords;
    int code;
} vector;

unsigned dim = 0;
unsigned learningAmount = 0;

vector W = NULL;

double multiplyVectors(vector u, vector v)
{
    double sum = 0;
    assert(dim > 0);
    for(int i = 0; i < dim; ++i)
    {
        sum += u.cords[i] * v.cords[i];
    }
    return sum;
}

vector multiplyVectorByScalar(vector x, double s)
{
    assert(dim != 0);
    for (int i = 0; i < dim; ++i) {
        x.cords[i] *= s;
    }
    return x;
}

/**
 * add the second vector to the first vector
 * @param u
 * @param v
 */
void addVectors(vector u, vector v)
{
    assert(dim != 0);
    for(int i = 0; i < dim; ++i)
    {
        u.cords[i] += v.cords[i];
    }
}

void initW()
{
    assert(dim != 0);
    double *W_cords;
    W_cords = malloc(sizeof(double) * dim);
    memset(W_cords, sizeof(double), dim);
    W.code = 5;
    W.cords = W_cords;
    // TODO: free this malloc
    // TODO: malloc might fail.
}

double sign(double d)
{
   if( d > 0)
   {
       return 1.0;
   }
   return -1.0;
}



/**
 *
 * @return
 */
vector updateW(vector x)
{
    assert(dim != 0);
    double y_tag = sign(
            multiplyVectors(x,W)
    );

    if(y_tag != x.code)
    {
        updateW(
                multiplyVectorByScalar(x, y_tag)
        );
    }
}
vector createVectorFromString(char *str)
{
   vector v = NULL;

}

void processInputByState(input_state state, char *in)
{
    char **str = NULL; // leftover from the input (not a number)
    switch(state)
    {
        case(is_dim):
            dim = strtol(in, str, 10);
           break;
        case(is_in_lines):
            dim = strtol(in, str, 10);
            break;
        case(is_examples):
            break;
        case(is_work):
            break;

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

}

/**
 * Reads the input from a file
 * @param fileName file name to access for the input
 * @return error if could not process the file, 0 otherwise.
 */
io_error getFileInput(char *fileName)
{
    FILE *inputFile = fopen(fileName, "r");
    char *token = NULL;
    char data[MAX_CHARS_IN_LINE];

    if(!fgets)

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


int main(int argc, char *argv[])
{
    return 0;

}
