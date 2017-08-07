#include <stdio.h>
#include <math.h>

#define ALPHA 0.012299
#define BETA (1 - ALPHA)


long double xpos;
long double ypos;
long double xvelo;
long double yvelo;
long double time;
long steps;
long show_steps;
long step_size;

/**
 * String I'm gonna need later
 * Enter initial pos x:\n
 * Enter initial pos y:\n
 * Enter initial vel x:\n
 * Enter initial vel y:\n
 * Enter total time T:\n
 * Enter num of steps:\n
 * Enter num of steps to save:\n
 */

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
    return (xpos + 2 * yvelo - BETA * (xpos + ALPHA) / d1() - ALPHA * (xpos - BETA) / d2());
}

/**
 * VELOCITY
 * a_y
 */
long double ay()
{
    return (ypos - 2 * xvelo - BETA * (ypos) / d1() - ALPHA * (ypos) / d2());
}

/**
 * what's a single step of the road
 */
void single_step()
{
    xpos = (xpos + xvelo * step_size);
    ypos = (ypos + yvelo * step_size);
    xvelo = ax();
    yvelo = ay();
}

/**
 * preform multiple steps of the thing
 */
void multiple_steps() 
{
    for (int i = 0; i < show_steps ;i++)
    {
        printf("%Lf , %Lf", xpos, ypos);
        single_step();

    }
}


int main ()
{
    xpos = 0.994;
    ypos = 0.0;
    xvelo = 0.0;
    yvelo = -2.00158510638;
    time = 17.0652165602;
    steps = 10;
    show_steps = 10;
    step_size = (time/steps);
    multiple_steps();

    return 0;
}

