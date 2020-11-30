#pragma once

#include <vector>

#include "Graph.h"
#include "Airport.h"

using namespace std;

class ShortestPathFinder {
public:
    ShortestPathFinder();
    ShortestPathFinder(const Graph & graph);
    ~ShortestPathFinder();
    
    /**
     * Dijkstra's algorithm
     */
    vector<Airport> getShortestPath(Airport start, Airport end);
    
    /**
     * Landmark path algorithm
     */
    vector<Airport> getLandmarkPath(Airport start, Airport toVisit, Airport end);
    
private:
    Graph graph_;
    vector<Airport> data;
    
    
};
