/* 
Simulates a vibrating string 
Written by Nicholas Crane
*/

#include <stdio.h>
#include "../vec3.hpp"

#define double long double

static int N = 3;
static double mu = 0.1;
static double Lo = 1;
static double k = 1000; // k is equal to the stiffness alpha

class Node 
{
    public:
        vec3d s,v;
        Node() {s=vec3d(0,0,0);v=vec3d(0,0,0);}
        Node(vec3d pos, vec3d vel)
        {
            s = pos;
            v = vel;
        }
        ~Node() {}
};

vec3d springForce(vec3d pos1, vec3d pos, vec3d pos2)
{
    return ((pos-pos1)*(1/(pos-pos1).mag())*(pos-pos1) + (pos-pos2)*(1/(pos-pos2).mag())*(pos-pos2))*k;
}

int main()
{
    double m = mu*Lo/N;
    double ro = Lo/(N-1);


}