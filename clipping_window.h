#ifndef CLIPPING_WINDOW_H_
#define CLIPPING_WINDOW_H_

#include <string>

#include "config.h"

using namespace std;

class ClippingWindow {
public:

	ClippingWindow() {
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
		end_x = WIDTH;
		end_y = HEIGHT;
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
		return 0;//(start_x <= end_x) ? start_x : end_x;
	}

	int get_max_x() {
		return 400; //(start_x >= end_x) ? start_x : end_x;
	}

private:
	bool is_clipping;
	int end_x, end_y;
	int start_x, start_y;

};

#endif
