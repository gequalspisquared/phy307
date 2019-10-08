/* Simulates a pendulum and demonstrates the amplitude does affect the period */
#include <stdio.h>
#include <math.h>
#define  double   long double

/* Set up general parameters */
static double g  = 9.81;
static double r  = 1;
static double L  = 10;

/* Returns the absolute value of a double */
int zabs(double x) {
	if (x < 0)
		return 0;
	return 1;
}

double dabs(double x) {
	if (x < 0)
		return -x;
	return x;
}

/* Returns the angular acceleration of the pendulum */
double alpha(double theta) {return -g/L*sin(theta);}

void main(int argc, char* argv[]) {
	// double theta = M_PI/20736; /* initial theta, must be in radians */
	double theta = 1e-12; /* used for testing small angle approximation */
	double omega = 0;
	double thetaMax, fractionalPeriod;
	double t = 0;
	double dt = 1e-6;
	double t1 = 0, t2 = 0;
	double x, y;
	double period;
	double T = 2*M_PI*sqrt(L/g);
	int sign ;

	for(thetaMax = 1e-6; thetaMax < 2; thetaMax *= 10) {
		theta = thetaMax;
		t = t1 = t2 = 0;
		while(t < 1e1) { /* loops through the simulation */
			if (*argv[1] == '1') { /* this section is just used for anim */
				x = L*sin(theta);
				y = -L*cos(theta);

				printf("l3 0 0 0 %Le %Le 0\n", x, y);
				printf("c3 %Le %Le  0 %Le\n", x, y, r);
				printf("F\n");
			}

			else if (*argv[1] == '2') { /* print theta as a function of time */
				printf("%Le %Le\n", t, theta);
			}

			else if (*argv[1] == '3') { /* print omega as a function of time */
				printf("%Le %Le\n", t, omega);
			}

			else {}

			sign = zabs(omega);
			theta += omega*dt/2;
			omega += alpha(theta)*dt;
			theta += omega*dt/2;
			t += dt;

			if (zabs(omega) != sign) {
				if (t == dt)
					continue;
				if (t1 < dt) {
					t1 = t - omega/alpha(theta);
				}
				else if (t2 < dt) {
					t2 = t - omega/alpha(theta);
					period = (t2-t1)*2;
					fractionalPeriod = (period-T)/T;
				}
			}
		}
		printf("%Le %Le\n", period, fractionalPeriod);
		if (thetaMax > 0.9)
			thetaMax /= 5;
	}

	if (*argv[1] == '1') { /* this section is just used for anim */
		x = L*sin(theta);
		y = -L*cos(theta);

		printf("l3 0 0 0 %Le %Le 0\n", x, y);
		printf("c3 %Le %Le  0 %Le\n", x, y, r);
		printf("F\n");
	}

	else if (*argv[1] == '2') { /* print theta as a function of time */
		printf("%Le %Le\n", t, theta);
	}

	else if (*argv[1] == '3') { /* print omega as a function of time */
		printf("%Le %Le\n", t, omega);
	}

	else {}

	// printf("%Le %Le %.15Le\n", t1, t2, period);
	// printf("%Le\n",dabs(T-period));

}
