#ifndef EDGE_TABLE_H_
#define EDGE_TABLE_H_

#include <map>
#include <vector>
#include <iostream>

#include "point.h"
#include "config.h"

using namespace std;

class EdgeTable {

public:

	EdgeTable() {
	}

	EdgeTable( vector<Edge> edges ) {

		for ( auto &edge : edges ) {
			// skip all horizontal lines, not needed
			if ( edge.is_horizontal_line() ) {
				continue;
			}
			edge_table.insert( pair<int, Edge>( edge.get_min_y(), edge ) );
		}

	}

	void push_active_edges( int y, vector<Edge> &active_edge_list ) {
		int count = edge_table.count( y );
		if ( count > 0 ) {
			multimap<int, Edge>::const_iterator itr = edge_table.find(y);
			for(int i = 0; i < count; ++i){
				active_edge_list.push_back((*itr).second);
				++itr;
			}
		}
	}

	friend ostream& operator<<( ostream& os, const EdgeTable& et ) {
		for ( multimap<int, Edge>::const_iterator it = et.edge_table.begin();
				it != et.edge_table.end(); ++it ) {
			os << "[" << (*it).first << ", " << (*it).second << "]" << endl;
		}

		return os;
	}

private:
	// y, edge associated with a given y
	multimap<int, Edge> edge_table;

};

#endif
