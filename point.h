#ifndef POINT_H_
#define POINT_H_

#include <string>
#include <iostream>

#include "config.h"

using namespace std;

class Point {
public:
	Point( int x, int y ) :
			x( x ), y(HEIGHT - 1 - y ) {
	}

	int get_x() {
		return this->x;
	}

	int get_y(){
		return y;
	}

	friend ostream& operator<<( ostream& os, const Point& p ) {
		os << "(" << p.x << ", " << p.y << ")";
		return os;
	}

private:
	int x;
	int y;
};

#endif
