#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class Color{

public:
	double r, g, b;

	Color(){
		while(true){
			r = ((double) rand() / (RAND_MAX));
			g = ((double) rand() / (RAND_MAX));
			b = ((double) rand() / (RAND_MAX));

			if ( r > 0.1 && g > 0.1 && b > 0.1 ) {
				break;
			}
		}
	}

	friend ostream& operator<<( ostream& os, const Color& c ) {
		os << "R: " << c.r << " G: " << c.g << " B: " << c.b;
		return os;
	}

};

#endif
