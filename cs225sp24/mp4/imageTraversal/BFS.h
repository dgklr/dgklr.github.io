#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include <queue>
#include <set>

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  vector <Point> _path;
  queue <Point> q;
  set <pair<int, int> > in;
};

#endif
