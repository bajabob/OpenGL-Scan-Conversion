#ifndef CLIPPING_WINDOW_H_
#define CLIPPING_WINDOW_H_

#include <string>

#include "color.h"
#include "config.h"

using namespace std;

class ClippingWindow {
public:

	ClippingWindow() :
			color( 1.0, 1.0, 1.0 ) {
		is_clipping = false;
		reset();
	}

	bool can_clip() {
		return is_clipping;
	}

	void toggle_clip() {
		is_clipping = !is_clipping;
	}

	void reset() {
		start_x = 0;
		start_y = 0;
		end_x = WIDTH-1;
		end_y = HEIGHT-1;
	}

	void set_start_points( int x, int y ) {
		start_y = HEIGHT - 1 - y;
		start_x = x;
		end_x = x + 1;
		end_y = start_y + 1;
	}

	void set_end_points( int x, int y ) {
		end_x = x;
		end_y = HEIGHT - 1 - y;
	}

	int get_min_y() {
		return (start_y <= end_y) ? start_y : end_y;
	}

	int get_max_y() {
		return (start_y >= end_y) ? start_y : end_y;
	}

	int get_min_x() {
		return (start_x <= end_x) ? start_x : end_x;
	}

	int get_max_x() {
		return (start_x >= end_x) ? start_x : end_x;
	}

	void draw( float (&framebuffer)[HEIGHT][WIDTH][3] ) {
		if ( is_clipping ) {
			for ( int x = get_min_x(); x < get_max_x(); ++x ) {
				// top of window
				color.draw( x, get_min_y(), framebuffer );
				// bottom of window
				color.draw( x, get_max_y(), framebuffer );
			}
			for ( int y = get_min_y(); y < get_max_y(); ++y ) {
				// left of window
				color.draw( get_min_x(), y, framebuffer );
				// right of window
				color.draw( get_max_x(), y, framebuffer );
			}
		}
	}

private:
	Color color;
	bool is_clipping;
	int end_x, end_y;
	int start_x, start_y;

};

#endif
