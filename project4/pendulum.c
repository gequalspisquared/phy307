/* Simulates a pendulum and demonstrates the amplitude does affect the period */
#include <stdio.h>
#include <math.h>
#define  double   long double

/* Set up general parameters */
static double g  = 9.81;
static double r  = 1;
static double L  = 10;
static double dt = 1e-6;

/* Returns the absolute value of a double */
int dabs(double x) {
	if (x < 0)
		return 0;
	return 1;
}

/* Returns the angular acceleration of the pendulum */
double alpha(double theta) {return -g/L*sin(theta);}

void main(int argc, char* argv[]) {
	double theta = M_PI/20736; /* initial theta, must be in radians */
	double omega = 0;
	double t = 0;
	double t1 = 0, t2 = 0;
	double x, y;
	double period;
	int sign ;

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

		sign = dabs(omega);
		theta += omega*dt/2;
		omega += alpha(theta)*dt;
		theta += omega*dt/2;
		t += dt;

		if (dabs(omega) != sign) {
			if (t == dt)
				continue;
			if (t1 < dt) {
				t1 = t;
			}
			else if (t2 < dt) {
				t2 = t;
				period = (t2-t1)*2;
			}
		}
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

	printf("%Le %Le %.12Le\n", t1, t2, period);
}
