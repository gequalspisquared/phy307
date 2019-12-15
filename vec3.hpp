/* 
Uses classes to create a vector math library
Written by Nicholas Crane
Made with assistance from Jim Doxtader 
*/


#include <math.h>
#define double long double

class vec3d
{
	public:
		vec3d() {i = 0, j = 0, k = 0;}
		vec3d(double x, double y, double z) {
			i = x; 
			j = y; 
			k = z;
		}

		~vec3d() {}

		double get_i() {return i;}
		double get_j() {return j;}
		double get_k() {return k;} 

		inline vec3d operator+(vec3d vector){
			double x = i + vector.get_i();
			double y = j + vector.get_j();
			double z = k + vector.get_k();
			return vec3d(x,y,z);
		}

		inline void operator+=(vec3d vector) {
			i += vector.get_i();
			j += vector.get_j();
			k += vector.get_k();
		}

		inline vec3d operator-(vec3d vector) {
			double x = i - vector.get_i();
			double y = j - vector.get_j();
			double z = k - vector.get_k();
			return vec3d(x,y,z);
		}

		inline vec3d operator*(double scalar) {
			return vec3d(scalar*i,scalar*j,scalar*k);
		}

		inline vec3d operator*(vec3d vector) {
			return vec3d(vector.get_i()*i,vector.get_j()*j,vector.get_k()*k);
		}

		inline double mag() {
			return sqrt(i*i+j*j+k*k);
		}

		double dot(vec3d vec) {
			return i*vec.get_i()+
				   j*vec.get_j()+
				   k*vec.get_k();
		}

		// vec3d cross(vec3d vec) {
		// 	double x,y,z;
        // 	x = (j*vec.get_k())-(k*vec.get_j());
        // 	y = (k*vec.get_i())-(i*vec.get_k());
		// 	z = (i*vec.get_j())-(j*vec.get_i());
		// 	return vec3d(x,y,z);
		// }

	private:
		double i,j,k;
};