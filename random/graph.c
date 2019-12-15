#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main(int argc, char* argv[]) 
{
    int i,n=atoi(argv[1]);
    double yeet;
    double x=0,dx=0.00001;


    while(x < M_PI)
    {
        yeet = 0;
        for(i = 2; i <= n; i += 2) {
            yeet += (pow(-1,i)+1)/(1-i*i)*cos(i*x);
        }

        printf("%f %f\n",x,2/M_PI + (2/M_PI)*yeet);
        x += dx;
    }
}