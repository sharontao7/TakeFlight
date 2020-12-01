/**
* @file BFS.h
*/

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "Graph.h"
#include "Airport.h"
#include "ImageTraversal.h"

class BFS : public ImageTraversal {
public:
    BFS(const Graph & graph, const Vertex & start);
    ~BFS();

    ImageTraversal::Iterator begin();
    ImageTraversal::Iterator end();

    void add(const Vertex & airport); // airport?
    Vertex pop();
    Vertex peek() const;
    bool empty() const;
    
private:
    /** @todo [Part 1] */
    /** add private members here*/
    Graph graph_;
    Vertex start_;
    std::queue<Vertex> airports_;
    bool * visited_;
};
