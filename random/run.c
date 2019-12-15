#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) 
{
    int n = atoi(argv[1]);
    char command[51];
    snprintf(command,sizeof(command),"./graph %d > graph.txt",n);
    system("gcc graph.c -o graph -lm");
    system(command);
    system("gnuplot -p 'plot.gp'");
}