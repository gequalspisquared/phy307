/*  Simulates celestial bodies in motion  */
/*  Written by Nicholas Crane
	Vector library made with assistance from Jim Doxtader  */

#include <stdio.h>
#include <math.h>
#include "../vec3.hpp" 

#define double long double
#define NUMBODIES 2

static double G = 4*M_PI*M_PI;

class Body 
{
	public:
		double m,r;
		vec3d s,v;
		Body() {s = vec3d(0,0,0);v = vec3d(0,0,0);m = 1e-6;r = 1e-1;}
		Body(vec3d pos, vec3d vel, double mass, double radius)
		{
			s = pos; 
			v = vel;
			m = mass;
			r = radius;
		}
};

vec3d forceG(double m1, double m2, vec3d pos1, vec3d pos2)
{
	return (pos1-pos2)*(-G*m1*m2/pow((pos1-pos2).mag(),3));
}

int main() 
{
	double t = 0;
	double dt = 1e-2;
	int i,j;
	vec3d force;

	Body body[NUMBODIES];
	body[0] = Body(vec3d(0,0,0),vec3d(0,0,0),1,0.25);
	body[1] = Body(vec3d(1,0,0),vec3d(0,2*M_PI,0),3.3e-5,0.05);

	while (true)
	{
		for(i = 0; i < NUMBODIES; i++)
		{
			body[i].s += body[i].v*(dt/2);
		}

		for(i = 0; i < NUMBODIES; i++)
		{
			for(j = (i+1); j < NUMBODIES; j++)
			{
				force = forceG(body[i].m,body[j].m,body[i].s,body[j].s);
				body[i].v += force*(dt/body[i].m);
				body[j].v += force*(-dt/body[j].m);
			}
		}

		for(i = 0; i < NUMBODIES; i++)
		{
			body[i].s += body[i].v*(dt/2);
		}

		for(i = 0; i < NUMBODIES; i++)
		{
			printf("c3 %Le %Le %Le %Le\n",body[i].s.get_i(),body[i].s.get_j(),body[i].s.get_k(),body[i].r);
		}

		printf("T -0.9 0.8\n");
		printf("E = %.15Le\n",(body[1].v.mag()*body[1].v.mag())*0.5 - G/(body[1].s-body[0].s).mag());
		printf("T -0.9 0.7\n");
		printf("r = %.15Le\n",(body[1].s-body[0].s).mag());
		printf("F\n");
	}
}
