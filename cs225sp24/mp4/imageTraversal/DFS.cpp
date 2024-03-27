#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"
#include <iostream>

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
    const int step[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    add(start);
    while (!empty()) {
        Point now = pop();
        if (in.find(make_pair(now.x, now.y)) != in.end()) continue;
        _path.push_back(now);
        in.insert(make_pair(now.x, now.y));
        for (int ns = 0; ns < 4; ns ++) {
            int tmpx = now.x + step[ns][0], tmpy = now.y + step[ns][1];
            if (tmpx < 0 || tmpy < 0 || tmpy >= (int)png.height() || tmpx >= (int)png.width())
                continue;
            //if (in.find(make_pair(tmpx, tmpy)) != in.end())
            //    continue;
            if (calculateDelta(*png.getPixel(tmpx, tmpy), *png.getPixel(start.x, start.y)) < tolerance)
                add(Point(tmpx, tmpy));
        }
    }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  return (_path.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  return (_path.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
    Point ret = q.top();
    q.pop();
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  return q.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return q.empty();
}
