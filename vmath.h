// Useful for basic vector operations

#include <math.h>

typedef struct vector {
	double i,j,k;
} vector;

vector vadd(vector vector1, vector vector2) {
	vector resultant;
	resultant.i = vector1.i + vector2.i;
	resultant.j = vector1.j + vector2.j;
	resultant.k = vector1.k + vector2.k;
	return resultant;
}

vector vsub(vector vector1, vector vector2) {
	vector resultant;
	resultant.i = vector1.i - vector2.i;
	resultant.j = vector1.j - vector2.j;
	resultant.k = vector1.k - vector2.k;
	return resultant;
}

vector vmul(vector vector1, vector vector2) {
	vector resultant;
	resultant.i = vector1.i * vector2.i;
	resultant.j = vector1.j * vector2.j;
	resultant.k = vector1.k * vector2.k;
	return resultant;
}

vector vdiv(vector vector1, vector vector2) {
	vector resultant;
	resultant.i = vector1.i / vector2.i;
	resultant.j = vector1.j / vector2.j;
	resultant.k = vector1.k / vector2.k;
	return resultant;
}

vector vcro(vector vector1, vector vector2) {
	vector resultant;
	resultant.i = vector1.j*vector2.k - vector1.k*vector2.j;
	resultant.j = vector1.k*vector2.i - vector1.i*vector2.k;
	resultant.k = vector1.i*vector2.j - vector1.j*vector2.i;
	return resultant;
}

vector vsca(double scalar, vector *vector) {
	double *i=&vector->i,*j=&vector->j,*k=&vector->k;
	vector->i = *i*scalar;
	vector->j = *j*scalar;
	vector->k = *k*scalar;
}

double vdot(vector vector1, vector vector2) {
	double result;
	result = vector1.i*vector2.i + 
	         vector1.j*vector2.j + 
	         vector1.k*vector2.k;
	return result;
}

double vlen(vector vector) {
	double result;
	result = sqrt(pow(vector.i,2) 
		   +      pow(vector.j,2)
		   +      pow(vector.k,2));
	return result;
}

double vdis(vector vector1, vector vector2) {
	double result;
	result = sqrt(pow(vector1.i-vector2.i,2)
		   +      pow(vector1.j-vector2.j,2)
		   +      pow(vector1.k-vector2.k,2));
	return result;
}
