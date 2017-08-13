#define MAX_CHARS_IN_LINE 400
#define INPUT_DELIM ","
#define NUMBERS_BASE 10
#define MINIMUM_ARGS 2

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
    err_sys_err = 3
} io_error;

typedef struct Vectors {
    double *cords;
    int code;
} vector;

