#include <stdio.h>
#include <math.h>

#define ALPHA 0.012299
#define BETA (1 - ALPHA)


long double XPOS;
long double YPOS;
long double XVELO;
long double YVELO;
long double TIME;
long steps;
long show_steps;
long step_size;

/**
 * D_1
 */
long double d1()
{
    return powl(
            (powl((xpos + ALPHA), 2) + powl(ypos, 2)),
            (1.5)
        );
}

/**
 * D_2
 */
long double d2()
{
    return powl(
            (powl((xpos - BETA), 2) + powl(ypos, 2)),
            (1.5)
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

void single_step()
{
    xpos = xpos + xvelo * step_size;
    ypos = ypos + yvelo * step_size;
    xvelo = ax();
    yvelo = ay();
}

void multiple_steps() 
{
    for (int i = 0; i < numsteps ;i++)
}


int main ()
{
    step_size = (time/numsteps);
    return 0;
}

