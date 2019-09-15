/* Computes the error of different types of integration algorithms */ 

#include <stdio.h>
#include <math.h>
/*#define double float
#define sin sinf*/

double dabs(double n) {
	if (n < 0)
		return -n;
	return n;
}

double impIntegrate(double (*function)(double), double leftBound, double rightBound, int binNum) {
	double ans=0,var,stepSize=(rightBound-leftBound)/binNum;

	for(var = leftBound; var < rightBound; var += stepSize) {
		ans += function(var)*stepSize;
	}
	return ans;
}

double sine(double x) {
	return sin(x);
}

void main() {
	int binSize;

	for(binSize = 2; binSize < 10000000; binSize *= 10) {
		printf("%d %f\n",binSize,dabs(1.416147 - impIntegrate(sine,0,2,binSize)));
	}
}
