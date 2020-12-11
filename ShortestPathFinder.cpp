/**
 * @file ShortestPathFinder.cpp
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>

#include "ShortestPathFinder.h"

ShortestPathFinder::ShortestPathFinder() : graph_(true, true) {
    readAirportData("airports.dat");
    readRouteData("routes.dat");
}

ShortestPathFinder::ShortestPathFinder(string airportFile, string routeFile) : graph_(true, true) {
    readAirportData(airportFile);
    readRouteData(routeFile);
}

ShortestPathFinder::~ShortestPathFinder() {
    airports.clear();
}

int ShortestPathFinder::calculateDistance(Vertex start, Vertex end) {
    Airport sourceLoc = airports[start];
    Airport destLoc = airports[end];
    
    // convert decimal lat/lon values to radians
    double lat1 = (M_PI * sourceLoc.getLatitude()) / 180;
    double lat2 = (M_PI * destLoc.getLatitude()) / 180;
    double lon1 = (M_PI * sourceLoc.getLongitude()) / 180;
    double lon2 = (M_PI * destLoc.getLongitude()) / 180;
    
    // get delta lat & delta lon
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    
    // use haversine formula to calculate distance between radian values
    double dist = pow(sin(dLat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dLon / 2), 2);
    dist = 2 * 6371 * asin(sqrt(dist));
    
    return (int) dist;
}

void ShortestPathFinder::readAirportData(string fileName) {
    ifstream infile(fileName);
    
    while (infile) {
        string line;
        if (!getline(infile, line))
            break;
        istringstream s(line);
        
        int infoNum = 0;
        string ID, name;
        double lat, lon;
        
        // read in ID, name, lat, lon
        while (s) {
            string word;
            if (!getline(s, word, ',' ))
                break;
            if (infoNum == 0) {                     // ID
                ID = word;
            } else if (infoNum == 1) {              // Name
                name = word;
            } else if (infoNum == 6) {               // latitude
                stringstream lat_string(word);
                lat_string >> lat;
            } else if (infoNum == 7) {              // longitude
                stringstream lon_string(word);
                lon_string >> lon;
            }
            infoNum++;
        }

        // create new Airport obj and add to airports
        Airport airport = Airport(ID, name, lat, lon);
        airports[ID] = airport;

        // insert airport ID as vertex into graph
        if (!graph_.vertexExists(ID))
            graph_.insertVertex(ID);
    }
    if (!infile.eof())
    {
        cerr << "Airports data file could not be read.\nPlease enter 0 to exit the program.\n";
    }
    
    /*
    // print dictionary
    for (std::pair<string, Airport> airport : airports) {
        std::cout << "Airport: " << airport.second.getName() << " " << airport.second.getLatitude() << " " << airport.second.getLongitude() << std::endl;
    }
    */
}

void ShortestPathFinder::readRouteData(string fileName) {
    ifstream infile(fileName);
    
    while (infile) {
        string line;
        if (!getline(infile, line))
            break;
        istringstream s(line);
        
        int infoNum = 0;
        string sourceID, destID;
        
        // read in sourceID, destID for airports
        while (s) {
            string word;
            if (!getline(s, word, ',' ))
                break;
            if (infoNum == 3) {
                sourceID = word;
            } else if (infoNum == 5) {
                destID = word;
            }
            infoNum++;
        }
        
        // insert edge between source & destination vertices in graph
        if (graph_.vertexExists(sourceID) && graph_.vertexExists(destID)) {
            graph_.insertEdge(sourceID, destID);
            
            // set distance between source & dest as edge weight
            int dist = calculateDistance(sourceID, destID);
            graph_.setEdgeWeight(sourceID, destID, dist);
        }
        
    }
    
    if (!infile.eof())
    {
        cerr << "Routes data file could not be read.\nPlease enter 0 to exit the program.\n";
    }
}

void ShortestPathFinder::buildPath(map<string, string> &previous, string &dest, vector<Airport>& path) {
    // Base Case : If j is source
    if (previous[dest] == "*") {
        path.push_back(airports[dest]);
        return;
    }
 
    buildPath(previous, previous[dest], path);
    path.push_back(airports[dest]);
}

void ShortestPathFinder::printPath(vector<Airport> path) {
    cout << endl << "Shortest Path (using Dijkstra's Algorithm):" << endl;
    
    if (path.empty()) {
        cout << "No possible path found." << endl;
    }
    
    for (Airport airport : path) {
        cout << airport.getID() << " " << airport.getName() << endl;
    }
    
    cout << endl;
}

vector<Airport> ShortestPathFinder::getShortestPath(Vertex start, Vertex end) {
    vector<Airport> path;
    bool destReached = false;
    
    if (!graph_.vertexExists(start) || !graph_.vertexExists(end)) {
        return path;
    }
    
    // queue stores remaining airports, ordered by distance
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> airportQueue;
    map<string, int> distMap;
    map<string, string> previous;
    
    // insert starting airport into queue
    airportQueue.emplace(0, start);
    distMap[start] = 0;
    previous[start] = "*";
    
    // initialize all starting distances (other than starting airport) to "infinity"
    // parents are undefined for now
    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (it->first != start) {
            distMap[it->first] = INT_MAX;
            previous[it->first] = "";
        }
    }
    
    while (!airportQueue.empty()) {
        pair<int, string> curr = airportQueue.top();
        airportQueue.pop();
        
        // end if destination airport has been found & accounted for already
        if (curr.second == end) {
            destReached = true;
            break;
        }
        
        // iterate through neighbors for current airport
        vector<Vertex> neighbors = graph_.getAdjacent(curr.second);
        for (Vertex neighbor : neighbors) {
            // get total distance from current airport to neighbor
            // if this is less than the current distance stored, insert into queue
            int dist = graph_.getEdgeWeight(curr.second, neighbor) + curr.first;
            if (dist < distMap[neighbor]) {
                distMap[neighbor] = dist;
                previous[neighbor] = curr.second;
                airportQueue.emplace(dist, neighbor);
            }
        }
    }
    
    if (destReached) {
        buildPath(previous, end, path);
    }
    
    return path;
}

vector<Airport> ShortestPathFinder::buildLandmarkPath(vector<Airport> pathA, vector<Airport> pathB) {
    vector<Airport> fullPath;
    
    // if either endpoint could not could not be reached, no valid path
    if (pathA.empty() || pathB.empty()) {
        return fullPath;
    }
    
    // combine two paths in correct order
    for (unsigned i = 0; i < pathA.size(); i++) {
        fullPath.push_back(pathA.back());
        pathA.pop_back();
    }
    fullPath.insert(fullPath.end(), pathB.begin(), pathB.end());
    
    return fullPath;
}

vector<Airport> ShortestPathFinder::getLandmarkPath(Vertex start, Vertex end, Vertex landmark) {
    vector<Airport> pathA;
    vector<Airport> pathB;
    vector<Airport> path;
    int destReached = 0;
    
    if (!graph_.vertexExists(start) || !graph_.vertexExists(end) || !graph_.vertexExists(landmark)) {
        return path;
    } else if (graph_.getAdjacent(start).empty() || graph_.getAdjacent(end).empty() || graph_.getAdjacent(landmark).empty()) {
        return path;
    }
    
    // queue stores remaining airports, ordered by distance
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> airportQueue;
    map<string, int> distMap;
    map<string, string> previous;
    
    // insert starting airport into queue
    airportQueue.emplace(0, landmark);
    distMap[landmark] = 0;
    previous[landmark] = "*";
    
    // initialize all starting distances (other than starting airport) to "infinity"
    // parents are undefined for now
    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (it->first != landmark) {
            distMap[it->first] = INT_MAX;
            previous[it->first] = "";
        }
    }
    
    while (!airportQueue.empty()) {
        pair<int, string> curr = airportQueue.top();
        airportQueue.pop();
        
        // end if destination airport has been found & accounted for already
        if (curr.second == start || curr.second == end) {
            destReached++;
        }
        
        if (destReached == 2)
            break;
        
        // iterate through neighbors for current airport
        vector<Vertex> neighbors = graph_.getAdjacent(curr.second);
        for (Vertex neighbor : neighbors) {
            // get total distance from current airport to neighbor
            // if this is less than the current distance stored, insert into queue
            int dist = graph_.getEdgeWeight(curr.second, neighbor) + curr.first;
            if (dist < distMap[neighbor]) {
                distMap[neighbor] = dist;
                previous[neighbor] = curr.second;
                airportQueue.emplace(dist, neighbor);
            }
        }
    }
    
    if (destReached == 2) {
        buildPath(previous, start, pathA);
        buildPath(previous, end, pathB);
    }
    
    path = buildLandmarkPath(pathA, pathB);
    return path;
}

void ShortestPathFinder::printCompleteBFS() {
    cout << endl << "Complete BFS Traversal (all components)" << endl;
    
    // set all vertices and edges to unexplored/unvisited
    map<Vertex, bool> visited;
    for (Vertex v : graph_.getVertices()) {
        visited[v] = false;
    }
    for (Edge e: graph_.getEdges()){
        graph_.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    
    // traverse all vertices, visit unexplored vertices in BFS order
    for (Vertex v : graph_.getVertices()) {
        if (visited[v] == false) {
            queue<Vertex> traversal;
            visited[v] = true;
            cout << "Airport: " << v << " " << airports[v].getName() << endl;
            traversal.push(v);
            
            while (!traversal.empty()) {
                Vertex curr = traversal.front();
                traversal.pop();
                
                // visit neighbors of current vertex
                for (Vertex w : graph_.getAdjacent(curr)) {
                    if (visited[w] == false) {
                        graph_.setEdgeLabel(curr, w, "DISCOVERY");
                        visited[w] = true;
                        cout << "Airport: " << w << " " << airports[w].getName() << endl;
                        traversal.push(w);
                    } else {
                        if (graph_.getEdgeLabel(curr, w) == "UNEXPLORED") {
                            graph_.setEdgeLabel(curr, w, "CROSS");
                        }
                    }
                }
            }
        }
    }
    
    cout << endl;
}

void ShortestPathFinder::printBFS(Vertex start_) {
    cout << endl << "BFS Traversal (component of given airport only)" << endl;
    
    if (!graph_.vertexExists(start_)) {
        cout << "Airport ID does not exist." << endl << endl;
        return;
    }
    
    map<Vertex, bool> visited;
    queue<Vertex> traversal;
    
    // visit starting vertex/airport first
    visited[start_] = true;
    cout << "Airport: " << start_ << " " << airports[start_].getName() << endl;
    traversal.push(start_);
    
    // visit all vertices within same component
    while (!traversal.empty()) {
        Vertex curr = traversal.front();
        traversal.pop();
        
        // visit all neighboring vertices
        for (Vertex neighbor : graph_.getAdjacent(curr)) {
            if (visited[neighbor] == false) {
                graph_.setEdgeLabel(curr, neighbor, "DISCOVERY");
                visited[neighbor] = true;
                cout << "Airport: " << neighbor << " " << airports[neighbor].getName() << endl;
                traversal.push(neighbor);
            } else {
                if (graph_.getEdgeLabel(curr, neighbor) == "UNEXPLORED") {
                    graph_.setEdgeLabel(curr, neighbor, "CROSS");
                }
            }
        }
    }
    
    cout << endl;
}

void ShortestPathFinder::printGraph() {
    graph_.print();
}

void ShortestPathFinder::printNeighbors(Vertex airport) {
    if (!graph_.vertexExists(airport)) {
        cout << endl << "Airport ID does not exist." << endl << endl;
        return;
    }
    
    vector<Vertex> neighbors = graph_.getAdjacent(airport);
    
    cout << endl;
    
    for (Vertex neighbor : neighbors) {
        cout << airports[neighbor]
             << " is " << graph_.getEdgeWeight(airport, neighbor) << " km away." << endl;
    }
    
    cout << endl;
}

Graph ShortestPathFinder::getGraph() {
    return graph_;
}
