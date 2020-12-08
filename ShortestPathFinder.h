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
    vector<Airport> getShortestPath(Vertex start, Vertex end);
    
    /**
     * Landmark path algorithm
     */
    vector<Airport> getLandmarkPath(Vertex start, Vertex end, Vertex toVisit);
    
    vector<Airport> BFSTraversal();
    
private:
    Graph graph_;
    map<string, Airport> airports;
    
    void readAirportData(string filename);      // initialize airports & vertices in graph
    void readRouteData(string filename);        // create edges iin graph

    string closestAirport(map<string, int> distMap, map<string, bool> airportSet);
    
    vector<Airport> bfs(Vertex start, Vertex end);
};
