#ifndef POLYGON_MANAGER_H_
#define POLYGON_MANAGER_H_

#include <string>
#include <vector>
#include <iostream>

#include "point.h"
#include "color.h"
#include "config.h"
#include "polygon.h"
#include "clipping_window.h"

using namespace std;

class PolygonManager {

public:

	PolygonManager() {
		create_new_poly = true;
	}

	void add_point( int x, int y ) {
		if ( create_new_poly ) {
			if ( polygons.size() >= MAX_POLYGONS ) {
				cerr << "Max number of polygons added (" << MAX_POLYGONS << ")"
						<< endl;
				return;
			}
			create_new_poly = false;
			Polygon p;
			polygons.push_back( p );
		}
		polygons.back().add_point( x, y );
	}

	void add_final_point( int x, int y ) {
		if ( polygons.back().size() < 2 ) {
			cerr << "Polygon requires at least three points "
					<< "to be considered a polygon!" << endl;
			return;
		}
		if ( create_new_poly ) {
			cerr << "Right-click already pressed. Left click "
					<< "to add a new polygon." << endl;
			return;
		}
		create_new_poly = true;
		polygons.back().add_final_point( x, y );
	}

	void draw_verticies( float (&framebuffer)[HEIGHT][WIDTH][3] ) {
		for ( int i = 0; i < polygons.size(); ++i ) {
			polygons[i].draw_verticies( framebuffer );
		}
	}

	void draw_fill( float (&framebuffer)[HEIGHT][WIDTH][3],
			ClippingWindow &cw ) {

		// fill the buffer
		for ( int y = 0; y < HEIGHT; ++y ) {
			for ( int i = 0; i < polygons.size(); ++i ) {
				polygons[i].draw_fill( y, framebuffer, cw );
			}
		}

		// cleanup any leftover elements in the edge list
		for ( int i = 0; i < polygons.size(); ++i ) {
			polygons[i].clear_active_edge_list();
		}

	}

	friend ostream& operator<<( ostream& os, const PolygonManager& pm ) {
		os << "Polygons:" << endl;
		for ( auto &polygon : pm.polygons ) {
			os << "=> " << polygon << endl;
		}
		return os;
	}

private:

	bool create_new_poly;
	vector<Polygon> polygons;

};

#endif
