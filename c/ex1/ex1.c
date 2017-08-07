#include <stdio.h>
#include <math.h>

#define ALPHA 0.012299
#define BETA (1 - ALPHA)
long double xpos,ypos,x_velocity,y_velocity,time,step_size;
long total_steps, show_steps;

int main();
int checkValidInputFile(FILE *pFILE);
long double d1();
long double d2();
long double accelerateX();
long double accelerateY();
void inputFromFile(FILE *inputFile, FILE *outputFile);
void inputFromUser(FILE *outputFile);
void singleMove();
void arenstorfRoute();


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
long double next_xpos;
long double next_ypos;
long double next_x_velocity;
long double next_y_velocity;
/**
 *
 */
void singleMove() {

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
void arenstorfRoute() {
    for (int i = 0; i < total_steps; ++i)
    {
        singleMove();
        if ( i % (total_steps / show_steps) == 0)
        {
            printf("%.3Le , %.3Le\n",xpos ,ypos);
            // write location to file
        }
    }
}
int main(){
    xpos = 0.994;
    ypos = 0.0;
    x_velocity = 0.0;
    y_velocity = -2.00158510638;
    time = 17.0652165602;
    total_steps = 10;
    show_steps = 10;
    arenstorfRoute();
}

void inputFromFile(FILE *inputFile, FILE *outputFile) {
    if (checkValidInputFile(inputFile))
    {

    }
    else
    {
        // handle the exception
    }

}
/**
 *
 * @param pFILE
 * @return
 */
unsigned checkValidInputFile(FILE *pFILE) {
    return 1;
}

/**
 *
 * @param outputFile
 */
void inputFromUser(FILE *outputFile) {

}



