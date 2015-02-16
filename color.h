#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <cstdlib>
#include <iostream>

#include "point.h"
#include "config.h"

using namespace std;

class Color {

public:
	double r, g, b;

	Color() {
		while (true) {
			r = ((double) rand() / (RAND_MAX));
			g = ((double) rand() / (RAND_MAX));
			b = ((double) rand() / (RAND_MAX));

			if ( r > 0.1 && g > 0.1 && b > 0.1 ) {
				break;
			}
		}
	}

	void draw( Point &point, float (&framebuffer)[HEIGHT][WIDTH][3] ) {
		int y = point.get_translated_y();
		int x = point.get_x();
		framebuffer[y][x][0] = r;
		framebuffer[y][x][1] = g;
		framebuffer[y][x][2] = b;
	}

	friend ostream& operator<<( ostream& os, const Color& c ) {
		os << "R: " << c.r << " G: " << c.g << " B: " << c.b;
		return os;
	}

};

#endif
