/**
 * @file BFS.h
 * Based on BFS.h from mp_traversals, CS 225 FA 20
*/

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "Graph.h"
#include "Airport.h"
#include "Traversal.h"

class BFS : public Traversal {
public:
    BFS(const Graph & graph, const Vertex & start);

    Traversal::Iterator begin();
    Traversal::Iterator end();

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
};
