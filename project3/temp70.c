/* Analyzes the Euler and RK2 methods for solving ODEs */
/* Takes in two arguments
   arg1: 0 for Euler's Method or 1 for RK2 or anything else for analytic
   arg2: 1 to print final time 0 to not print it */

#include <stdio.h>
#include <math.h>
#define  double   long double /* Uses long doubles, more accurate than standard doubles */
#define  ANSWER   log((70-30)/(100-30))/(-0.1) /* numeric solution for when T = 70 */

/* Returns the change in Temp w.r.t. time */
double dTemp(double currentTemp, double ambientTemp, double k) {
	return -k*(currentTemp - ambientTemp);
}

/* Returns the change in currentTemp using Euler's method */
double euler(double currentTemp, double ambientTemp, double k, double dt) {
	return dTemp(currentTemp, ambientTemp, k)*dt;
}

/* Return the change in currentTemp using the RK2 method */
double runge(double currentTemp, double ambientTemp, double k, double dt) {
	return dTemp(currentTemp + dTemp(currentTemp, ambientTemp, k)*dt/2, ambientTemp, k)*dt;
}

/* Returns the answer to the analytic solution of the ODE */
double analytic(double t) {
	return 30 + (100 - 30) * exp(-0.1*t);
}

double dabs(double x) {
	if (x < 0) 
		return -1*x;
	return x;
}

void main(int argc, char* argv[]) {
	double currentTemp = 100 ; /* This is the initial temperature                */
	double ambientTemp = 30  ; /* Ambient temp outside the object                */
	double k           = 0.1 ; /* The cooling constant, found through experiment */
	double dt          = 1.0 ; /* The size of the time step                      */
	double t           = 0   ; /* Keeps track of the time                        */
	double tDone             ; /* Used to find precisely when currentTemp = 70   */
	double targetTemp  = 70  ; /* This is the target used to test our methods    */
	int i              = 1   ; /* used for switching between values of dt */


	for(i = 0; i < 7; dt /= 10, i++) {
		currentTemp = 100;
		t           = 0  ;
		if (*argv[1] == '0') { /* Use Euler's Method */
			while(currentTemp > targetTemp) {
				// printf("%Lf %Le\n", t, currentTemp);
				currentTemp += euler(currentTemp, ambientTemp, k, dt);
				t += dt;
			}
			// printf("%.6Lf %Le\n", t, currentTemp);
			if (*argv[2] == '1') {
				// tDone = t - (currentTemp - targetTemp)/(euler(currentTemp, ambientTemp, k, dt)/dt);
				tDone = t;
				// printf("%Le %Le\n", dt, dabs(currentTemp - analytic(5)));
				printf("%Le %Le\n", dt, dabs(analytic(tDone) - targetTemp));
			}
		}

		else if (*argv[1] == '1') { /* Use the RK2 Method */
			while(currentTemp > targetTemp) {
				// printf("%.6Lf %Le\n", t, currentTemp);
				currentTemp += runge(currentTemp, ambientTemp, k, dt);
				t += dt;
			}
			// printf("%.6Lf %Le\n", t, currentTemp);
			if (*argv[2] == '1') {
				tDone = t - (currentTemp - targetTemp)/(runge(currentTemp, ambientTemp, k, dt)/dt);
				// tDone = t - (currentTemp - targetTemp)/(euler(currentTemp, ambientTemp, k, dt)/dt);
				// printf("%Le %Le\n", dt, dabs(currentTemp - analytic(5)));
				printf("%Le %Le\n", dt, dabs(analytic(tDone) - targetTemp));
			}
		}

		else { /* Use the analytic method */
			while(currentTemp > targetTemp) {
				currentTemp =  analytic(t);
				printf("%.6Lf %Le\n", t, currentTemp);
				t += dt;
			}
			if (*argv[2] == '1') {
				tDone = t - (currentTemp - targetTemp)/(runge(currentTemp, ambientTemp, k, dt)/dt);
				// tDone = t - (currentTemp - targetTemp)/(euler(currentTemp, ambientTemp, k, dt)/dt);
				printf("The temperature reached 70 degrees at: %.15Le min\n",tDone);
			}
		}
	}
}
