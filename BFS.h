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

class BFS {
public:
    BFS(const Graph & graph, const Airport & start);
    ~BFS();
    
    // we need to change iterators
    // ImageTraversal::Iterator begin();
    // ImageTraversal::Iterator end();
    
    void add(const Airport & airport); // airport?
    Airport pop();
    Airport peek() const;
    bool empty() const;
    
private:
    /** @todo [Part 1] */
    /** add private members here*/
    Graph * graph_;
    Airport start_;
    std::queue<Airport> airports_;
    bool * visited_;
};
