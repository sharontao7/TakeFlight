#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>

#include "ShortestPathFinder.h"
#include "Graph.h"
#include "BFS.h"
#include "Traversal.h"

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
        graph_.insertEdge(sourceID, destID);
        
        // calculate dist between source & dest
        // set as edge weight
        Airport sourceLoc = airports[sourceID];
        Airport destLoc = airports[destID];
    
        double lon = destLoc.getLongitude() - sourceLoc.getLongitude();
        double lat = destLoc.getLatitude() - sourceLoc.getLatitude();
        
        double dist = 2 * 6371 *
                (asin(sqrt(pow(sin(lat / 2), 2) + cos(sourceLoc.getLatitude()) * cos(destLoc.getLatitude()) * pow(sin(lon / 2), 2))));
        graph_.setEdgeWeight(sourceID, destID, dist);
        
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
    
    if (pathA.empty() || pathB.empty()) {
        return fullPath;
    }
    
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
    int destReached = 0;
    
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
    
    return buildLandmarkPath(pathA, pathB);
}

void ShortestPathFinder::printBFS(Vertex start_) {
    if (!graph_.vertexExists(start_)) {
        cout << "Starting vertex does not exist." << endl << endl;
        return;
    }
    
    BFS bfs(graph_, start_);

    cout << endl << "BFS Traversal:" << endl;
    
    for(Traversal::Iterator it = bfs.begin();it != bfs.end(); ++it){
        cout << "Airport: " << *it << " " << airports[*it].getName() << endl;
    }
    
    cout << endl;
}

void ShortestPathFinder::printGraph() {
    graph_.print();
}

void ShortestPathFinder::printNeighbors(Vertex airport) {
    vector<Vertex> neighbors = graph_.getAdjacent(airport);
    
    cout << endl;
    
    for (Vertex neighbor : neighbors) {
        cout << neighbor
             << " distance between: " << graph_.getEdgeWeight(airport, neighbor) << " km" << endl;
    }
    
    cout << endl;
}
