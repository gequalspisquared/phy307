/* Analyzes the Euler and RK2 methods for solving ODEs */

#include <stdio.h>
#define  double   long double /* Uses long doubles, more accurate than standard doubles */
#define  METHOD   1           /* If 0, use Euler's method, otherwise use RK2 method */

/* Returns the change in Temp w.r.t. time */
double dTemp(double currentTemp, double ambientTemp, double k) {
	return -k*(currentTemp - ambientTemp);
}

double euler(double currentTemp, double ambientTemp, double k, double dt) {
	return currentTemp + dTemp(currentTemp, ambientTemp, k)*dt;
}

double runge(double currentTemp, double ambientTemp, double k, double dt) {
	return currentTemp + dTemp(currentTemp + dTemp(currentTemp, ambientTemp, k)*dt/2, ambientTemp, k)*dt;
}

void main() {
	double currentTemp = 100 ; /* This is the initial temperature                    */
	double ambientTemp = 30  ; /* Ambient temp outside the object                    */
	double k           = 0.1 ; /* The cooling constant, found through experiment     */
	double dt          = 1e-6; /* The size of the time step                          */
	double t           = 0   ; /* Keeps track of the time                            */
	double prevTemp          ; /* Used for calculating exactly when currentTemp = 70 */
	double tDone             ; /* Used to find precisely when currentTemp = 70       */
	double targetTemp  = 70  ; /* This is the target used to test our methods        */

	if (METHOD == 0) { /* Use Euler's Method */
		while(currentTemp > targetTemp) {
			currentTemp = euler(currentTemp, ambientTemp, k, dt);
			t += dt;
			printf("%.6Lf %Le\n", t, currentTemp);
		}
		// tDone = t - (currentTemp - targetTemp)/dTemp(currentTemp, ambientTemp, k);
		tDone = t;
	}
	else { /* Use the RK2 Method */
		while(currentTemp > targetTemp) {
			currentTemp += dTemp(currentTemp + dTemp(currentTemp, ambientTemp, k)*dt/2, ambientTemp, k)*dt;
			t += dt;
			// printf("%.6Lf %Le\n", t, currentTemp);
		}
		tDone = t - (currentTemp - targetTemp)/dTemp(currentTemp + dTemp(currentTemp, ambientTemp, k)*dt/2, ambientTemp, k);
		// tDone = t - (currentTemp - targetTemp)/dTemp(currentTemp, ambientTemp, k);
		printf("The temperature reached 70 degrees at: %.15Le min\n",tDone);
	}
}
