/* Automatically compiles and runs string2d */

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    int runAnim = atoi(argv[1]);
    int initialConditions = atoi(argv[2]);
    char command[51];
    system("g++ .cpp -O2 -o string2d -lm");
    
    if(runAnim == 1) {
        snprintf(command,sizeof(command),"./string2d %d %d | anim",runAnim,initialConditions);
    } else {
        snprintf(command,sizeof(command),"./string2d %d %d",runAnim,initialConditions);        
    }

    system(command);
    // system("gnuplot -p 'plot.gp'");
}