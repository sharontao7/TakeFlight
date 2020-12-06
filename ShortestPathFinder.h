#pragma once

#include <vector>
#include <map>
#include <string>

#include "Graph.h"
#include "Airport.h"

using namespace std;

class ShortestPathFinder {
public:
    ShortestPathFinder();
    ShortestPathFinder(string airportFile, string routeFile);
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
    map<string, Airport> airports;
    // can replace pair w Airport class later to hold more var
    // can also read airline data later to let user know what airline to take
    
    void readAirportData(string filename);      // initialize airports & vertices in graph
    void readRouteData(string filename);        // create edges iin graph
};
