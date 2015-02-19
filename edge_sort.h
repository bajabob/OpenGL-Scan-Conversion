#ifndef EDGE_SORT_H_
#define EDGE_SORT_H_

#include "edge.h"

using namespace std;

class EdgeSort {
      int y;
public:
      EdgeSort(int y) : y(y) {}
      bool operator()( Edge o1,  Edge o2) const {
            return o1.get_x_increment(y) < o2.get_x_increment(y);
      }
};

#endif
