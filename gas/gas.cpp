/*
Simulates a gas in a box 
Written by Nicholas Crane
*/

#include <stdio.h>
#include "../vec3.hpp"

#define double long double

/* General paramters for the simulation */
static int N = 2; // number of nodes
static int stepSize = 1; // used for speeding up anim
static double L = 10; // length of the bounding box
// static double A = 1e2; // equilibrium distance for forces
// static double R = 1e2;
static double ro = 0.25; // equilibrium distance for forces
static double n = 1e-1; // affects attractive force
static double m = 2e0; //affects repulsive force

/* General particle class */
class Particle
{
    public:
        vec3d s,v;
        double m,r;
        Particle() {s=vec3d(0,0,0),v=vec3d(0,0,0),m=1,r=0.1;}
        Particle(vec3d pos, vec3d vel, double mass, double rad) {
            s = pos;
            v = vel; 
            m = mass;
            r = rad;
        }
        ~Particle() {}
};

vec3d atomForce(vec3d pos1, vec3d pos2)
{
    vec3d pos = pos1-pos2;
    double mag = pos.mag();
    return ( pos*(pow(ro,m)*pow(mag,-n))- pos*(pow(ro,n)*pow(mag,-m)) );
}

int main()
{
    static double r = 0.25;
    double dt = 1e-2;
    double t = 0;
    double mass = 1;
    int i,j;
    int step = 0;
    vec3d force;

    Particle atom[N];
    atom[0] = Particle(vec3d(4,5,5),vec3d(0,0,0),1,r);
    atom[1] = Particle(vec3d(6,5,5),vec3d(0,0,0),1,r);

    while(true) {

        for(i = 0; i < N; i++) {
            atom[i].s += atom[i].v*(dt/2);
        }

        for(i = 0; i < (N-1); i++) {
            for(j = (i+1); j < N; j++) {
                force = atomForce(atom[i].s, atom[j].s);
                atom[i].v += force*(dt/atom[i].m);
                atom[j].v += force*(-dt/atom[j].m);
                printf("!%Le\n",force.get_i());
            }
        }

        for(i = 0; i < N; i++) {
            atom[i].s += atom[i].v*(dt/2);
        }

        t += dt;
        for(i = 0; i < N; i++) {
            printf("c3 %Le %Le %Le %Le\n",atom[i].s.get_i(),atom[i].s.get_j(),atom[i].s.get_k(),atom[i].r);
        }
        printf("F\n");
    }
}