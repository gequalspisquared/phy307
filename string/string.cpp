/* 
Simulates a vibrating string 
Written by Nicholas Crane
*/

#include <stdio.h>
#include "../vec3.hpp"

#define double long double

/* Parameters affecting the string */
static int N = 501; // the number of nodes
static double mu = 0.1; // the linear mass density of the string
static double Lo = 1; // the length of the unstretched string
static double k = 1000; // k is equal to the stiffness alpha
static double T = 1000; // initial tension along the string
static double r = 5e-3; // the radius of each node

/* A class containing the info for each node */
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

/* The equation for the force experienced by each node */
vec3d springForce(vec3d pos1, vec3d pos, vec3d pos2, double ro)
{
    return ( ((pos-pos1)*(1/(pos-pos1).mag())) * ((pos-pos1).mag() - ro) + ((pos-pos2)*(1/(pos-pos2).mag())) * ((pos-pos2).mag() - ro) )*-k;
}

int main()
{
    double m = mu*Lo/N; // mass of each node
    double ro = Lo/(N-1); // neutral distance between each node
    double L = (T/k) + Lo; // length of stretched wire
    double height = 0.1; // height of displaced point
    float dt = 0.0001;
    float t = 0;
    int i,j;

    /* Sets up initial conditions for each node */
    Node node[N];
    for(i = 0; i < N; i++)
    {
        if(i < ((N+2)/2)-1)
        {
            node[i] = Node(vec3d(i*(L/(N-1.0)) - L/2,height*i/(N/2),0),vec3d(0,0,0));
        }
        else if(i == ((N+1)/2)-1)
        {
            node[i] = Node(vec3d(i*(L/(N-1.0)) - L/2,height,0),vec3d(0,0,0));
        }
        else
        {
            node[i] = Node(vec3d(i*(L/(N-1.0)) - L/2,-height*(i-N/2)/(N/2) + height,0),vec3d(0,0,0));
        }
        
    }

    // while(t < 0.1)
    while(true)
    {
		for(i = 0; i < (N-1); i++) // update the position of each node 
		{
			node[i].s += node[i].v*(dt/2);
		}

		for(i = 1; i < (N-1); i++) // update the velocity of each node
		{
			node[i].v += springForce(node[i-1].s,node[i].s,node[i+1].s,ro)*(dt/m);
		}

		for(i = 0; i < (N-1); i++) // update the position of each node again
		{
			node[i].s += node[i].v*(dt/2);
		}


        t += dt;
        for(i = 0; i < N; i++)
        {
            printf("c3 %Le %Le %Le %Le\n",node[i].s.get_i(),node[i].s.get_j(),node[i].s.get_k(),r);
        }

        // printf("!%Le\n",node[1].v.get_j());
        printf("F\n");
    }
}