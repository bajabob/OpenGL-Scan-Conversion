#ifndef EDGE_H_
#define EDGE_H_

#include <cmath>
#include <vector>
#include <iostream>

#include "point.h"
#include "config.h"

using namespace std;

class Edge {

public:

	Edge( Point a, Point b ) :
			a( a ), b( b ) {

		y_max = (a.get_y() >= b.get_y()) ? a.get_y() : b.get_y();
		y_min = (a.get_y() <= b.get_y()) ? a.get_y() : b.get_y();

		// x-value of end-point with lowest y-value
		if ( y_min == a.get_y() ) {
			x_current = a.get_x();
		} else {
			x_current = b.get_x();
		}

		int y_diff = (b.get_y() - a.get_y());
		int x_diff = (b.get_x() - a.get_x());

		if ( x_diff == 0 ) {
			x_increment = 0;
		} else {
			x_increment = ((double) y_diff / (double) x_diff);
		}

		is_horizontal = (y_diff == 0) ? true : false;
		y_intercept = a.get_y() - x_increment * a.get_x();
	}

	int get_x_increment( int y ) {
		return (y - y_intercept) / x_increment;
	}

	bool is_horizontal_line() {
		return is_horizontal;
	}

	int get_max_y() {
		return y_max;
	}

	int get_min_y() {
		return y_min;
	}

	friend ostream& operator<<( ostream& os, const Edge& e ) {
		os << "a:" << e.a << " b:" << e.b << " slope:" << e.x_increment;
		return os;
	}

private:
	Point a;
	Point b;

	int y_min;
	int y_max;
	int x_current;
	double x_increment;
	double y_intercept;
	bool is_horizontal;

};

#endif
