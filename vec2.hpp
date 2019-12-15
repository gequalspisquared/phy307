/* 
Uses classes to create a vector math library
Written by Nicholas Crane
Made with assistance from Jim Doxtader 
*/


#include <math.h>
#define double long double

class vec2d
{
	public:
		vec2d() {i = 0,j = 0;}
		vec2d(double x, double y) {
            i = x; 
            j = y;
        }

		~vec2d() {}

		double get_i() {return i;}
		double get_j() {return j;}

		inline vec2d operator+(vec2d vector) {
			double x = i + vector.get_i();
			double y = j + vector.get_j();
			return vec2d(x,y);
		}

		inline void operator+=(vec2d vector) {
			i += vector.get_i();
			j += vector.get_j();
		}

		inline vec2d operator-(vec2d vector) {
			double x = i - vector.get_i();
			double y = j - vector.get_j();
			return vec2d(x,y);
		}

		inline vec2d operator*(double scalar) {
			return vec2d(scalar*i,scalar*j);
		}

		inline vec2d operator*(vec2d vector) {
			return vec2d(vector.get_i()*i,vector.get_j()*j);
		}

		inline double mag() {
			return sqrt(i*i+j*j);
		}

		double dot(vec2d vec) {
			return i*vec.get_i()+j*vec.get_j();
		}

		// vec2d cross(vec2d vec)
		// {
		// 	double x,y,z;
        // 	x = (j*vec.get_k())-(k*vec.get_j());
        // 	y = (k*vec.get_i())-(i*vec.get_k());
		// 	z = (i*vec.get_j())-(j*vec.get_i());
		// 	return vec2d(x,y,z);
		// }

	private:
		double i,j;
};