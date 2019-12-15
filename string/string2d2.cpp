/* 
Simulates a vibrating string 
Written by Nicholas Crane
*/

#include <stdio.h>
#include "../vec2.hpp"

#define double long double

/* Independent parameters affecting the string, you can change these */
static const int N = 1000; // the number of nodes, must be odd currently
static const int mode = 1; // the mode of the string (number of troughs + peaks)
static const int stepSize = 100; // used for speeding up anim
static const double mu = 1; // the linear mass density of the string
static const double Lo = 1; // the length of the unstretched string
static const double a = 10; // the stiffness 
static const double T = 10; // initial tension along the string
static const double amp = 0.1; // the amplitude of the string
static const double sigma = 0.3; // used for the Gaussian deformation
static const double r = 1e-2; // the radius of each node

/* Dependent parameters, DO NOT TOUCH */ 
static const double kstring = a/Lo; // spring constant of the whole string
static const double k = N*kstring; // spring constant of segments of string
static const double m = mu*Lo/N; // mass of each node
static const double L = (T/kstring)+Lo; // length of stretched wire
static const double ro = Lo/(N-1); // neutral distance between each node
static const double v = sqrt((T*L)/(Lo*mu)); // analytic velocity of waves
static const double w = 2*L/mode; // wavelength
static const double pan = w/v; // analytic period

/* A class containing the info for each node */
class Node 
{
    public:
        vec2d s,v;
        Node() {s=vec2d(0,0);v=vec2d(0,0);}
        Node(vec2d pos, vec2d vel) {
            s = pos;
            v = vel;
        }
        ~Node() {}
};

/* The equation for the force experienced by each node */
vec2d springForce(vec2d pos1, vec2d pos, vec2d pos2, double ro, double k)
{
    vec2d p1 = pos - pos1;
    vec2d p2 = pos - pos2;
    return (p1*(1-ro/p1.mag()) 
           +p2*(1-ro/p2.mag()))*-k;
}

vec2d dampForce(double j)
{
    return vec2d(0,j*-0.001);
}

/* Used for testing some initial conditions */
double expl(double x)
{
    return pow(M_E,x);
}

int signCheck(double x) 
{
    if(x < 0) {
        return 0;
    }
    return 1;
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
    double potential,kinetic; // used for calculating elastic and kinetic energy
    double period,oldt=0,diff; // used for determining the period
    double dt=1e-5,t=0;
    int i,j,sign,antiNode;
    int step=0,fCount=0;
    // double maxU = 0;

    diff = 0;
    t = 0;
    // printf("!%Lf\n",pan);
    // printf("!%Lf\n",amp);
        
    /* Used for determining the frequency */
    if(N % 2 == 0) {
        antiNode = (N-3)/mode;
    } else {
        antiNode = (N-2)/mode;
    }

    /* Sets up initial conditions for each node */
    Node node[N];
    for(i = 0; i < N; i++) {
        if(*argv[2] == '0') { // Gaussian deformation
            node[i] = Node(vec2d(i*(L/(N-1.0)) - L/2,0),vec2d(0,0));
            node[i].s = vec2d(i*(L/(N-1.0))-L/2,amp*expl(-pow(node[i].s.get_i(),2)/(sigma*sigma)));
        }
            
        if(*argv[2] == '1') { // superposition of normal modes
                node[i] = Node(vec2d(i*(L/(N-1.0)),0),vec2d(0,0));
            node[i].s = vec2d(i*(L/(N-1.0))-L/2,amp*sin(mode*node[i].s.get_i()*M_PI/L));
        }

        if(i > 0) {
            node[i].s += vec2d(0,-node[0].s.get_j());
        }
    }
    node[0].s += vec2d(0,-node[0].s.get_j());

    /* Runs the simulation */
    while(t < 60) {

        sign = signCheck(node[antiNode].v.get_j());

        for(i = 0; i < (N-1); i++) { // update the position of each node 
            node[i].s += node[i].v*(dt/2);
        }

        for(i = 1; i < (N-1); i++) { // update the velocity of each node
            node[i].v += (springForce(node[i-1].s,node[i].s,node[i+1].s,ro,k)+dampForce(node[i].v.get_j()))*(dt/m);
        }

        if(signCheck(node[antiNode].v.get_j()) != sign) {
            if(t > 0) {
                fCount++;
                    
                period = 2*(t-oldt);
                oldt = t;
                diff = abs(pan-period)/period;
                // printf("!%Lf\n",diff);
                printf("%.6Lf %.6Lf\n",t,1/period);
            }
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

        if(*argv[1] == '1') {
            if(step % stepSize == 0) {
                for(i = 0; i < N; i++) { // sends information to anim
                    printf("c %Le %Le %Le\n",node[i].s.get_i(),node[i].s.get_j(),r);
                }

                printf("T -0.9 0.8\n");
                printf("E = %Le + %Le = %Le\n",kinetic,potential,kinetic+potential);
                printf("T -0.9 0.7\n");
                printf("f = %.5Lf\n",period);
                printf("T -0.9 0.6\n");
                printf("t = %.2Le\n",t);
                printf("F\n");
            }
        }
    }
    // printf("maxU = %Le\n",maxU);
}