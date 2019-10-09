/* Simulates point charges in 3D space */

#include <stdio.h>
#include "vec3.hpp"

#define NUMPARTICLE 3

static double k = 8.99e9;

class Particle
{
	public:
		vec3d s,v;
		double m,q,r;
		double get_m() {return m;}
		double get_q() {return q;}
		Particle() {s = vec3d(0,0,0); v = vec3d(0,0,0); m = 1e-3; q = 1.6e-19; r = 1e-1;}
		Particle(vec3d pos, vec3d vel, double mass, double charge, double radius)
		{
			s = pos; 
			v = vel;
			m = mass;
			q = charge;
			r = radius;
		}
};

vec3d electricForce(double q1, double q2, vec3d pos1, vec3d pos2)
{
	double mag = (pos1-pos2).mag();
	return (pos1-pos2)*(k*q1*q2*pow(mag,-3));
}

int main() 
{
	int i,j;
	double t = 0;
	double dt = 1e-2;
	vec3d force;

	Particle particle[NUMPARTICLE];
	particle[0] = Particle(vec3d(1,1,1),vec3d(0,0,0),1,1e-5,0.25);
	particle[1] = Particle(vec3d(0,0,0),vec3d(0,0,0),1,1e-5,0.25);
	particle[2] = Particle(vec3d(-1,-1,-1),vec3d(0,0,0),1,1e-5,0.25);

	while(true)
	{
		for(i = 0; i < NUMPARTICLE; i++)
		{
			particle[i].s += particle[i].v*(dt/2);
			for(j = (i+1); j < NUMPARTICLE; j++)
			{
				force = electricForce(particle[i].q,particle[j].q,particle[i].s,particle[j].s);
				particle[i].v += force*(dt/particle[i].m);
				particle[j].v += force*(-dt/particle[j].m);

			}
			particle[i].s += particle[i].v*(dt/2);
		}
		t += dt;
		for(i = 0; i < NUMPARTICLE; i++)
			printf("c3 %Le %Le %Le %Le\n",particle[i].s.get_i(),particle[i].s.get_j(),particle[i].s.get_k(),particle[i].r);
		printf("F\n");
	}


	return 0;
}
