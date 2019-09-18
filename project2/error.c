/* Computes the error of different types of integration algorithms */ 

#include <stdio.h>
#include <math.h>
/*#define double float
#define sin sinf*/
#define double long double
// Allows for switching between using floats and doubles easily

// Returns the absolute value of a function
double dabs(double n) {
	if (n < 0)
		return -n;
	return n;
}

// Computes the integral of a function using the Left-Hand Rule
double leftIntegrate(double (*function)(double), double leftBound, double rightBound, int binNum) {
	double ans=0,var,stepSize=(rightBound-leftBound)/binNum;

	for(var = leftBound; var < rightBound; var += stepSize) {
		ans += function(var)*stepSize;
	}
	return ans;
}

// Computes the integral of a function using the Mid-Point Rule
double midpIntegrate(double (*function)(double), double leftBound, double rightBound, int binNum) {
	double ans=0,var,stepSize=(rightBound-leftBound)/binNum;

	for(var = leftBound+(stepSize/2); var < rightBound; var += stepSize) {
		ans += function(var)*stepSize;
	}
	return ans;
}

// Computes the integral of a function using the Trapezoid Rule
double trapIntegrate(double (*function)(double), double leftBound, double rightBound, int binNum) {
	double ans=0,var,stepSize=(rightBound-leftBound)/binNum;
	ans += function(leftBound);

	for(var = leftBound+stepSize; var < rightBound-(stepSize/2); var += stepSize) {
		ans += 2*function(var);
	}

	ans += function(rightBound);
	return ans*(rightBound-leftBound)/(2*binNum);
}

double simpIntegrate(double (*function)(double), double leftBound, double rightBound, int binNum) {
	return (1.0/3)*(trapIntegrate(function,leftBound,rightBound,binNum)) + (2.0/3)*(midpIntegrate(function,leftBound,rightBound,binNum));
}

// This is the function we are analyzing
double sine(double x) {
	return sin(x);
}

double sqroot(double x) {
	return sqrt(x);
}

void main() {
	int binSize;

	for(binSize = 2; binSize < 21000000; binSize *= 10) {
		// printf("%8d %Le\n",binSize,dabs(cos(2) - 1 + leftIntegrate(sine,0,2,binSize)));
		// printf("%8d %Le\n",binSize,dabs(cos(2) - 1 + midpIntegrate(sine,0,2,binSize)));
		printf("%8d %Le\n",binSize,dabs(cos(2) - 1 + simpIntegrate(sine,0,2,binSize)));
		// printf("%8d %Le\n",binSize,dabs(cos(2) - 1 + trapIntegrate(sine,0,2,binSize)));
		// printf("%8d %Le\n",binSize,dabs((2.0/3)*pow(2,1.5) - 2.0/3 - midpIntegrate(sqroot,1,2,binSize)));
		// printf("%8d %6f %6f\n",binSize,dabs(1.416147 - leftIntegrate(sine,0,2,binSize)),binSize,dabs(1.416147 - midpIntegrate(sine,0,2,binSize)));
	}
}
