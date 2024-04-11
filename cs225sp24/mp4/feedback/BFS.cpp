
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
    const int step[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    add(start);
    while (!empty()) {
        Point now = pop();
        _path.push_back(now);
        for (int ns = 0; ns < 4; ns ++) {
            int tmpx = now.x + step[ns][0], tmpy = now.y + step[ns][1];
            if (tmpx < 0 || tmpy < 0 || tmpy >= (int)png.height() || tmpx >= (int)png.width())
                continue;
            if (in.find(make_pair(tmpx, tmpy)) != in.end())
                continue;
            if (calculateDelta(*png.getPixel(tmpx, tmpy), *png.getPixel(start.x, start.y)) < tolerance)
                add(Point(tmpx, tmpy));
        }
    }
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  return (_path.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return (_path.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  in.insert(make_pair(point.x, point.y));
  q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
    Point ret = q.front();
    q.pop();
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return q.empty();
}
