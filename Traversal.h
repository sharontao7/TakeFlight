/**
 * @file Traversal.h
 */
#pragma once

#include <iterator>
#include <vector>
#include <map>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Airport.h"
#include "Graph.h"

using namespace cs225;
using namespace std;

class Traversal {
public:
//Really confused about graph. Are we iterating through Airports or Vertexes?
  class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
  public:
    Iterator();

    Iterator & operator++();
    Vertex operator*();
    bool operator!=(const Iterator &other);

    Iterator(Graph graph, Vertex start, Traversal* traversal);

  private:
    Graph graph_;
    Vertex start_;
    Vertex current_; 
    Traversal* traversal_;
    bool isAtEnd_;
    map<Vertex,bool> visited;
  };

  
  virtual Iterator begin() = 0;
  virtual Iterator end() = 0;
  virtual void add(const Vertex & t) = 0;
  virtual Vertex pop() = 0;
  virtual Vertex peek() const = 0;
  virtual bool empty() const = 0;
};
