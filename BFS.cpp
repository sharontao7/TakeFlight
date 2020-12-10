/**
 * @file BFS.cpp
 * Based on BFS.cpp from mp_traversals, CS 225 FA 20
*/

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "BFS.h"
#include "cs225/PNG.h"
#include "Airport.h"
#include "Graph.h"
#include "Traversal.h"

using namespace cs225;

/**
 * Initializes a breadth-first Traversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const Graph & graph, const Vertex & start) {  
  start_ = start;
  graph_ = graph;
  airports_.push(start_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
Traversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  Iterator iterator_ = Traversal::Iterator(graph_, start_, this);
  return iterator_;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
Traversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return Traversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Vertex & airport) {
  /** @todo [Part 1] */
  airports_.push(airport);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Vertex BFS::pop() {
  /** @todo [Part 1] */
  Vertex toReturn = airports_.front();
  airports_.pop();
  return toReturn;
}

/**
 * Returns the current Point in the traversal.
 */
Vertex BFS::peek() const {
  /** @todo [Part 1] */
  return airports_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(airports_.empty()){
    return true;
  } else {
    return false;
  }
}
