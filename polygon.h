#ifndef POLYGON_H_
#define POLYGON_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "edge.h"
#include "color.h"
#include "point.h"
#include "config.h"
#include "edge_sort.h"
#include "edge_table.h"
#include "clipping_window.h"

using namespace std;

class Polygon {

public:
	Polygon() {
		y_lowest = HEIGHT;
		y_highest = 0;
		is_constructed = false;
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
		verify_y_bounds( p );
		points.push_back( p );
	}

	void add_final_point( int x, int y ) {
		// add final point to poly
		Point p( x, y );
		verify_y_bounds( p );
		points.push_back( p );

		// construct edges
		vector<Edge> edges;
		for ( int i = 0; i < points.size() - 1; ++i ) {
			Edge e( points[i], points[i + 1] );
			edges.push_back( e );
		}
		Edge e( points[0], points[points.size() - 1] );
		edges.push_back( e );

		// create edge table
		EdgeTable et( edges );
		edge_table = et;

		is_constructed = true;
	}

	void draw_verticies( float (&framebuffer)[HEIGHT][WIDTH][3] ) {
		for ( auto &point : points ) {
			color.draw( point, framebuffer );
		}
	}

	void clear_active_edge_list() {
		active_edge_list.clear();
	}

	void draw_fill( int y, float (&framebuffer)[HEIGHT][WIDTH][3],
			ClippingWindow &cw ) {

		// check for any active edge additions
		edge_table.push_active_edges( y, active_edge_list );

		// clear any edges no longer within the y
		for ( int i = active_edge_list.size() - 1; i >= 0; --i ) {
			if ( active_edge_list[i].get_max_y() <= y ) {
				active_edge_list.erase( active_edge_list.begin() + i );
			}
		}
		sort(active_edge_list.begin(), active_edge_list.end(), EdgeSort(y));
		for ( int i = 0; i < active_edge_list.size(); i += 2 ) {
			int x_1 = active_edge_list[i].get_x_increment( y );
			int x_2 = active_edge_list[i + 1].get_x_increment( y );
			int max_x = (x_1 >= x_2) ? x_1 : x_2;
			int min_x = (x_1 <= x_2) ? x_1 : x_2;
			if ( max_x > WIDTH || max_x < 0 || min_x > WIDTH || min_x < 0 ) {
				cerr << "Out of window drawing bounds" << endl;
				continue;
			}
			// nothing to draw (left side of clip)
			if ( min_x < cw.get_min_x() && max_x < cw.get_min_x() ) {
				continue;
			}
			// nothing to draw (right side of clip)
			if ( min_x > cw.get_max_x() && max_x > cw.get_max_x() ) {
				continue;
			}
			// trim left side of line (if needed)
			if ( min_x < cw.get_min_x() && max_x > cw.get_min_x() ) {
				min_x = cw.get_min_x();
			}
			// trim right side of line (if needed)
			if ( max_x > cw.get_max_x() && min_x < cw.get_max_x() ) {
				max_x = cw.get_max_x();
			}
			for ( int x = min_x; x < max_x; ++x ) {
				color.draw( x, y, framebuffer );
			}
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
	EdgeTable edge_table;
	vector<Edge> active_edge_list;
	int y_lowest, y_highest;
	bool is_constructed;

	void verify_y_bounds( Point p ) {
		if ( p.get_y() < y_lowest ) {
			y_lowest = p.get_y();
		}
		if ( p.get_y() > y_highest ) {
			y_highest = p.get_y();
		}
	}

};

#endif
