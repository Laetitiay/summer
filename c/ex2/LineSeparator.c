#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_CHARS_IN_LINE 400
#define INPUT_DELIM ","

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

/* variables */
unsigned dim = 0;
unsigned learningAmount = 0;
vector W;
vector buffer_vector;

int sign(double d)
{
   if( d > 0)
   {
       return 1;
   }
   return -1;
}

int multiplyVectors(vector u, vector v)
{
    double sum = 0;
    assert(dim > 0);
    for(unsigned i = 0; i < dim; ++i)
    {
        sum += u.cords[i] * v.cords[i];
    }
    return sign(sum);
}

vector multiplyVectorByScalar(vector x, int s)
{
    assert(dim != 0);
    for (unsigned i = 0; i < dim; ++i) {
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
    for(unsigned i = 0; i < dim; ++i)
    {
        u.cords[i] += v.cords[i];
    }
}


void closeWAndBuffer()
{
    free(W.cords);
    free(buffer_vector.cords);
}

void initWAndBuffer()
{
    assert(dim != 0);
    double *W_cords = malloc(sizeof(double) * dim);
    memset(W_cords, 0, dim);
    W.code = 1;
    W.cords = W_cords;
    double *buffer_cords = malloc(sizeof(double) * dim);
    buffer_vector.cords = buffer_cords;
    if(W_cords == NULL || buffer_cords == NULL)
    {
        closeWAndBuffer();
        exit(1);
    }
    // TODO: free those mallocs
    // TODO: malloc might fail.
}


/**
 *
 * @return
 */
vector updateW(vector x)
{
    assert(dim != 0);
    double y_tag = multiplyVectors(x,W);

    if(y_tag != x.code)
    {
        addVectors(
                W, multiplyVectorByScalar(x, x.code)
        );
    }
}
vector updateBufferVector(char *data, input_state state)
{
    assert(dim != 0);
    char *token;

    unsigned i = 0;
    token = strtok(data, INPUT_DELIM);
    buffer_vector.cords[i] = (double) strtold(token, NULL);
    i++;

    for(;i < dim; i++)
    {
        token = strtok(NULL, INPUT_DELIM);
        buffer_vector.cords[i] = (double) strtold(token, NULL);
    }
    if(state == is_learning)
    {
        token = strtok(NULL, INPUT_DELIM);
        buffer_vector.code = (int) strtold(token, NULL);
    }
}



void processInputByState(input_state state, char *in)
{
    switch(state)
   {
        case(is_dim):
            dim = (unsigned int) strtol(in, NULL, 10);
           initWAndBuffer();
           break;
        case(is_in_lines):
            learningAmount = (unsigned int) strtol(in, NULL, 10);
            break;
        case(is_learning):
            updateBufferVector(in, state);
            updateW(buffer_vector);
            break;
        case(is_work):
            updateBufferVector(in, state);
            printf("%d\n", multiplyVectors(W,buffer_vector));
            break;
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
    unsigned line_num = 0;
    input_state state = is_dim;
    char *x;

    if(!inputFile)
    {
        fclose(inputFile);
        return err_no_file;
    }
    if(!fgets(data, MAX_CHARS_IN_LINE, inputFile))
    {
        fclose(inputFile);
        return err_invalid_input;
    }
    do
    {
        processInputByState(state, data);
        if(state < is_learning)
        {
            state++;
        }
        else
        {
            if(line_num - 1 == learningAmount)
            {
                state++;
            }
        }
        line_num++;

    }while(fgets(data, MAX_CHARS_IN_LINE, inputFile));

    fclose(inputFile);

    return err_no_err;
}


int main(int argc, char *argv[])
{
    getFileInput(argv[1]);
    closeWAndBuffer();
    return 0;

}
