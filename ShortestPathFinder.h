/**
 * @file ShortestPathFinder.h
 */

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
    vector<Airport> getLandmarkPath(Vertex start, Vertex end, Vertex landmark);
    
    void printBFS(Vertex start);
    void printCompleteBFS();
    void printGraph();
    void printNeighbors(Vertex airport);
    void printPath(vector<Airport> path);
    Graph getGraph();

private:
    Graph graph_;
    map<string, Airport> airports;
    
    void readAirportData(string filename);      // initialize airports & vertices in graph
    void readRouteData(string filename);        // create edges in graph
    int calculateDistance(Vertex start, Vertex end);

    void buildPath(map<string, string> &previous, string &dest, vector<Airport>& path);
    vector<Airport> buildLandmarkPath(vector<Airport> pathA, vector<Airport> pathB);
};
