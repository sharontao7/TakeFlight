#pragma once

#include <vector>
#include <map>
#include <string>

#include "Graph.h"
#include "Airport.h"
#include "BFS.h"
#include "Traversal.h"

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
    
    void BFSTraversal(Vertex start);
    vector<Airport> BFSTraversal(Vertex start, Vertex end);
    
private:
    Graph graph_;
    map<string, Airport> airports;
    
    void readAirportData(string filename);      // initialize airports & vertices in graph
    void readRouteData(string filename);        // create edges iin graph

    string closestAirport(map<string, int> distMap, map<string, bool> airportSet);
    void printPath(vector<Airport> &path);
    void BuildPath(map<string, string> &previous, string &dest, vector<Airport>& path);
};
