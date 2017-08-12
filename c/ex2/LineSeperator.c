#include <stdio.h>
#include <assert.h>

struct Vectors {
    double *cords;
    int code;
} vector;
int dim;

double multiplyVectors(struct Vectors u, struct Vectors v)
{
    double sum = 0;
    assert(dim > 0);
    for(int i = 0; i < dim; i++)
    {
        sum += u.cords[i] * v.cords[i];
    }
    return sum;
}

/**
 * test multiply vectors
unsigned testMult()
{
    struct Vectors a;
    struct Vectors b;
    double arr1[2] = {1.0, 2.0};
    double arr2[2] = {3.0, 4.0};
    a.cords = arr1;
    b.cords = arr2;
    dim = 2;
    if (multiplyVectors(a,b) != 11)
        return 1;
    else
        return 0;

}
 */

struct Vectors calculateWhatever()
{
}


int main(int argc, char *argv[])
{
    return 0;

}
