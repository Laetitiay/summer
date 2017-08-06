#include <stdio.h>
#include <math.h>

#define ALPHA 0.012299
#define BETA 1 - ALPHA


long double xpos;
long double ypos;
long double xvelo;
long double yvelo;
long double time;
long steps;
long numsteps;


/**
 * D_1
 */
long double d1()
{
    return powl(
            (powl((xpos + ALPHA), 2) + powl(ypos, 2)),
            (3/2)
        );
}

/**
 * D_2
 */
long double d2()
{
    return powl(
            (powl((xpos - BETA), 2) + powl(ypos, 2)),
            (3/2)
        );
}


/**
 * VELOCITY
 * a_x
 */
long double ax()
{
    return xpos + 2 * yvelo - BETA * (xpos + ALPHA) / d1() - ALPHA * (xpos - BETA) / d2();
}

/**
 * VELOCITY
 * a_y
 */
long double ay()
{
    return ypos - 2 * xvelo - BETA * (ypos) / d1() - ALPHA * (ypos) / d2();
}



int main ()
{
    return 0;
}

void inputFromFile()
{
}
