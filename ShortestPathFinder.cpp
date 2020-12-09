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

string ShortestPathFinder::closestAirport(map<string, int> distMap, map<string, bool> airportSet) {
    int min = INT_MAX;
    string min_airport;

    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (airportSet.find(it->first) != airportSet.end() && airportSet[it->first] == false && distMap[it->first] <= min) {
            min = distMap[it->first];
            min_airport = it->first;
        }
    }
   
    return min_airport;
}

void ShortestPathFinder::printPath(vector<Airport> &path) {
    for (Airport airport : path) {
        cout << airport.getID() << " " << airport.getName() << endl;
    }
}

vector<Airport> ShortestPathFinder::getShortestPath(Vertex start, Vertex end) {
    vector<Airport> path;
    map<string, int> distMap;
    map<string, bool> airportSet;
    map<string, string> previous;
    
    distMap[start] = 0;
    previous[start] = "*";
    airportSet[start] = false;

    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (it->first != start) {
            distMap[it->first] = INT_MAX;
            airportSet[it->first] = false;
        }
    }
    
    // iterate through all airports
    for (int i = 0; i < airports.size(); i++) {
        Vertex curr = closestAirport(distMap, airportSet);
        airportSet[curr] = true;
        
        if (curr == end)
            break;
        
        // iterate through neighbors for current airport
        vector<Vertex> neighbors = graph_.getAdjacent(curr);
        for (Vertex neighbor : neighbors) {
            if (!airportSet[neighbor]) {
                // get total distance from current airport to neighbor
                // if this is less than the current distance stored, update distance value
                int dist = graph_.getEdgeWeight(curr, neighbor) + distMap[curr];
                if (dist < distMap[neighbor]) {
                    distMap[neighbor] = dist;
                    previous[neighbor] = curr;
                }
            }
        }
    }
    
    buildPath(previous, end, path);
    printPath(path);
    return path;

}

vector<Airport> ShortestPathFinder::getLandmarkPath(Vertex start, Vertex end, Vertex toVisit) {

    vector<Airport> ret;
    
    // use shortest path or bfs to find path from start to toVisit, toVisit to end & combine

    return ret;
}

void ShortestPathFinder::BFSTraversal(Vertex start_) {
    BFS bfs(graph_, start_);

    cout << "BFS Traversal" << endl;
    
    for(Traversal::Iterator it = bfs.begin();it != bfs.end(); ++it){
        cout << "Airport: " << *it << " " << airports[*it].getName() << endl;
    }
}

void ShortestPathFinder::printGraph() {
    graph_.print();
}

void ShortestPathFinder::printNeighbors(Vertex airport) {
    vector<Vertex> neighbors = graph_.getAdjacent(airport);
    
    for (Vertex neighbor : neighbors) {
        cout << neighbor
             << " distance between: " << graph_.getEdgeWeight(airport, neighbor) << " km" << endl;
    }
}
