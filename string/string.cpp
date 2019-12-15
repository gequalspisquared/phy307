/* 
Simulates a vibrating string 
Written by Nicholas Crane
*/

#include <stdio.h>
#include "../vec3.hpp"

#define double long double

/* Parameters affecting the string */
static int N = 100; // the number of nodes, must be odd currently
static int mode = 2; // the mode of the string (number of troughs + peaks)
static int stepSize = 100; // used for speeding up anim
static double mu = 1; // the linear mass density of the string
static double Lo = 1; // the length of the unstretched string
static double k = 1e1; // k is equal to the stiffness alpha
static double T = 1e1; // initial tension along the string
static double amp = 0.1; // the amplitude of the string
static double r = 1e-2; // the radius of each node

/* A class containing the info for each node */
class Node 
{
    public:
        vec3d s,v;
        Node() {s=vec3d(0,0,0);v=vec3d(0,0,0);}
        Node(vec3d pos, vec3d vel) {
            s = pos;
            v = vel;
        }
        ~Node() {}
};

/* The equation for the force experienced by each node */
vec3d springForce(vec3d pos1, vec3d pos, vec3d pos2, double ro)
{
    vec3d p1 = pos - pos1;
    vec3d p2 = pos - pos2;
    return (p1*(1-ro/p1.mag()) 
           +p2*(1-ro/p2.mag()))*-k;
}

/* Used for testing some initial conditions */
double expl(double x)
{
    return pow(M_E,x);
}

/* Used for testing max potential energy, not necessary */
// void max(double *max, double current) 
// {
//     if(*max < current) {
//         *max = current;
//     }
// }

int main(int argc, char* argv[])
{
    double m = mu*Lo/N; // mass of each node
    double ro = Lo/(N-1); // neutral distance between each node
    double L = (T/k)+Lo; // length of stretched wire
    double potential; // used for calculating elastic potential energy
    // double maxU = 0;
    double kinetic; // used for calculating kinetic energy
    double dt = 1e-3;
    double t = 0;
    int i,j;
    int step=0;

    /* Sets up initial conditions for each node */
    Node node[N];
    for(i = 0; i < N; i++) {
        if(*argv[2] == '0') {
            node[i] = Node(vec3d(i*(L/(N-1.0)) - L/2,0,0),vec3d(0,0,0));
            node[i].s = vec3d(i*(L/(N-1.0))-L/2,expl(pow(node[i].s.get_i(),2)* amp/(L*L)),0);
        }
        
        if(*argv[2] == '1') {
            node[i] = Node(vec3d(i*(L/(N-1.0)),0,0),vec3d(0,0,0));
            node[i].s = vec3d(i*(L/(N-1.0))-L/2,amp*sin(mode*node[i].s.get_i()*M_PI/L),0);
        }
        if(i > 0) {
            node[i].s += vec3d(0,-node[0].s.get_j(),0);
        }
    }
    node[0].s += vec3d(0,-node[0].s.get_j(),0);

    /* Runs the simulation */
    while(true) {
		for(i = 0; i < (N-1); i++) { // update the position of each node 
			node[i].s += node[i].v*(dt/2);
		}

		for(i = 1; i < (N-1); i++) { // update the velocity of each node
			node[i].v += springForce(node[i-1].s,node[i].s,node[i+1].s,ro)*(dt/m);
		}

		for(i = 0; i < (N-1); i++) { // update the position of each node again
			node[i].s += node[i].v*(dt/2);
		}

        /* Calculates the total elastic potential energy in the string */
        potential = pow((node[1].s-node[0].s).mag()-ro,2)*(k/2); 
        kinetic = 0;
        for(i = 1; i < (N-1); i++) {
            potential += pow((node[i+1].s-node[i].s).mag()-ro,2)*(k/2);
            kinetic += pow(node[i].v.mag(),2)*m/2;
        }
        // max(&maxU,potential);

        t += dt;
        step++;

        if(*argv[1] == '0') {
            if(step % stepSize == 0) {
                for(i = 0; i < N; i++) { // sends information to anim
                    printf("c3 %Le %Le %Le %Le\n",node[i].s.get_i(),node[i].s.get_j(),node[i].s.get_k(),r);
                }

                printf("T -0.9 0.8\n");
                printf("E = %Le + %Le = %Le\n",kinetic,potential,kinetic+potential);
                printf("T -0.9 0.7\n");
                printf("t = %.2Le\n",t);
                printf("F\n");
            }
        }
    }
    // printf("maxU = %Le\n",maxU);
}