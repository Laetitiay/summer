#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include "LineSeparator.h"


/**
 * Not really "sign". Returns 1 if d > 0, -1 otherwise.
 * @param d number
 * @return 1 if d > 0, -1 otherwise.
 */
int sign(double d)
{
   if( d > 0)
   {
       return 1;
   }
   return -1;
}


/**
 * "Multiply" two vectors.
 * @param u first vector
 * @param v second vector
 * @param dim dimension of the vectors
 * @return the "sign" of the product
 */
int innerProduct(vector *u, vector *v, unsigned dim)
{
    assert(dim > 0);
    double sum = 0;
    for(unsigned i = 0; i < dim; ++i)
    {
        sum += u->cords[i] * v->cords[i];
    }
    return sign(sum);
}

/**
 * Multiply a vector by a scalar.
 * @param x vector to multiply
 * @param s scalar to multiply by
 * @param dim dimension of the vector.
 * @return pointer to the received vector
 */
vector *multiplyVectorByScalar(vector *x, int s, unsigned dim)
{
    assert(dim != 0);
    for (unsigned i = 0; i < dim; ++i) 
    {
        x->cords[i] *= s;
    }
    return x;
}

/**
 * Add the second vector to the first vector.
 * @param u vector to add to
 * @param v vector to add
 * @param dim dimenstion of the vectors
 */
void addVectors(vector *u, vector *v, unsigned dim)
{
    assert(dim != 0);
    for(unsigned i = 0; i < dim; ++i)
    {
        u->cords[i] += v->cords[i];
    }
}


/**
 * frees the arrays of the two vectors we are using throught this program
 * @param W calculating vector
 * @param buffer_vector vector used to reading
 */
void closeWAndBuffer(vector *W, vector *buffer_vector)
{
    free(W->cords);
    free(buffer_vector->cords);
}

/**
 * initializes the two vectors we are using throught this program
 * @param W calculating vector
 * @param buffer_vector vector used to reading
 * @param dim dimension of the vectors
 */
io_error initWAndBuffer(vector *W, vector *buffer_vector, unsigned dim)
{
    assert(dim != 0);
    //W
    double *W_cords = malloc(sizeof(double) * dim);
    double *buffer_cords = malloc(sizeof(double) * dim);
    // maybe it failed?
    if(W_cords == NULL || buffer_cords == NULL)
    {
        closeWAndBuffer(W, buffer_vector);
        return err_sys_err;
    }
    // gonna zero them out.
    // used memset before, but valgrind says uninitialized.
    for(unsigned i = 0; i < dim; ++i)
    {
        buffer_cords[i] = 0;
        W_cords[i] = 0;
    }
    W->cords = W_cords;
    buffer_vector->cords = buffer_cords;
    return err_no_err;
}

/**
 * Updates the W vector according to the x vector
 * @param W W vector
 * @param x x vector
 * @param dim dimeinsion of the vectors
 */
void updateW(vector *W, vector *x, unsigned dim)
{
    assert(dim != 0);
    double y_tag = innerProduct(x, W, dim);

    if(y_tag != x->code)
    {
        addVectors(
                W, multiplyVectorByScalar(x, x->code, dim), dim
        );
    }
}

/**
 * updates the buffer vector by a string
 * @param data data to update vector with
 * @param state current state of the program
 * @param buffer_vector vector to update into
 * @param dim dimension of the vector
 */
void updateBufferVector(char *data, input_state state, vector *buffer_vector, unsigned dim)
{
    assert(dim != 0);
    char *token;
    unsigned i = 0;

    // first char
    token = strtok(data, INPUT_DELIM);
    buffer_vector->cords[i] = (double) strtold(token, NULL);
    i++;

    // rest of them
    for(; i < dim; i++)
    {
        token = strtok(NULL, INPUT_DELIM);
        buffer_vector->cords[i] = (double) strtold(token, NULL);
    }
    // we have a code if we are learning
    if(state == is_learning)
    {
        token = strtok(NULL, INPUT_DELIM);
        buffer_vector->code = (int) strtold(token, NULL);
    }
}



/**
 * Proceess input according to the state of the program.
 * This used to include two other states when I used global variables.
 * I learned that I'm not allowed to use thme so I had to change it a bit.
 * @param state state of the program
 * @param in input string
 * @param W W vector
 * @param buffer_vector buffer vector
 * @param dim dimension the vectors are in
 */
void processInputByState(input_state state, char *in, vector *W, vector *buffer_vector, unsigned dim)
{
    switch(state)
   {
        case(is_learning):
            updateBufferVector(in, state, buffer_vector, dim);
            updateW(W, buffer_vector, dim);
            break;
        case(is_work):
            updateBufferVector(in, state, buffer_vector, dim);
            printf("%d\n", innerProduct(W, buffer_vector, dim));
            break;
       default:
           break;
   }

}

/**
 * Reads the input from a file and process it
 * @param fileName file name to access for the input
 * @param W the W vector
 * @param buffer_vector buffer vector
 * @return error if could not process the file, 0 otherwise.
 */
io_error processFile(char *fileName, vector *W, vector *buffer_vector)
{
    FILE *inputFile = fopen(fileName, "r");
    char data[MAX_CHARS_IN_LINE];
    unsigned line_num = 0;
    unsigned dim = 0;
    unsigned learningAmount = 0;
    input_state state = is_dim;

    if(!inputFile)
    {
        fclose(inputFile);
        return err_no_file;
    }

    /* read fist line */
    if(!fgets(data, MAX_CHARS_IN_LINE, inputFile))
    {
        fclose(inputFile);
        return err_invalid_input;
    }

    do
    {
        if(state == is_dim) // used to be in processInputByState
        {
            dim = (unsigned int) strtol(data, NULL, NUMBERS_BASE);
            if(initWAndBuffer(W, buffer_vector, dim))
            {
                break;
            }
        }
        else if (state == is_in_lines) // used to be in processInputByState
        {
            learningAmount = (unsigned int) strtol(data, NULL, NUMBERS_BASE);
        }
        else
        {
            processInputByState(state, data, W, buffer_vector, dim);
        }
        if(state < is_learning)
        {
            state++;
        }
        else // >= is learning
        {
            if(line_num - 1 == learningAmount) // finished learning
            {
                state++;
            }
        }
        line_num++;

    }while(fgets(data, MAX_CHARS_IN_LINE, inputFile));

    fclose(inputFile);

    return err_no_err;
}

/**
 * runs the program on a file
 * @param fileName file for inpiut
 * @return 0 if succeeded, other value otherwise.
 */
io_error runProgram(char *fileName)
{

/* variables */
    vector W;
    vector buffer_vector;

    io_error err = processFile(fileName, &W, &buffer_vector);
    closeWAndBuffer(&W, &buffer_vector);
    return err;
}

/**
 * MAIN
 */
int main(int argc, char *argv[])
{
    if(argc < MINIMUM_ARGS)
    {
        return err_no_file;
    }
    return runProgram(argv[1]);

}
