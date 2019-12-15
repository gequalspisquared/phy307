/* Automatically compiles and runs string2d2 */

#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    int runAnim = atoi(argv[1]);
    int initialConditions = atoi(argv[2]);
    char command[51];
    system("g++ string2d2.cpp -O2 -o string2d2 -lm");
    
    if(runAnim == 1) {
        snprintf(command,sizeof(command),"./string2d2 %d %d | anim",runAnim,initialConditions);
    } else {
        snprintf(command,sizeof(command),"./string2d2 %d %d",runAnim,initialConditions);        
    }

    system(command);
    // system("gnuplot -p 'plot.gp'");
}