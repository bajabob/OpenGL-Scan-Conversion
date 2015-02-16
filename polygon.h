#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include <string>
#include <iostream>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "color.h"
#include "point.h"
#include "config.h"

using namespace std;

class Polygon {

public:
	Polygon() {

	}

	int size() {
		return points.size();
	}

	void add_point( int x, int y ) {
		if ( points.size() >= (MAX_POINTS - 1) ) {
			cerr << "This polygon already has nine points, add a final "
					<< "tenth point by right-clicking the screen." << endl;
			return;
		}
		Point p( x, y );
		points.push_back( p );
	}

	void add_final_point( int x, int y ) {
		Point p( x, y );
		points.push_back( p );
	}

	void draw_verticies( float (&framebuffer)[HEIGHT][WIDTH][3] ) {
		for ( auto &point : points ) {
			color.draw(point, framebuffer);
		}
	}

	friend ostream& operator<<( ostream& os, const Polygon& poly ) {
		for ( int i = 0; i < poly.points.size(); ++i ) {
			if ( i < poly.points.size() - 1 ) {
				os << poly.points[i] << ", ";
			} else {
				os << poly.points[i];
			}
		}
		return os;
	}

private:
	Color color;
	vector<Point> points;

};

#endif
