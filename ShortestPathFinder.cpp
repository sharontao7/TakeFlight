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
        string ID;
        double lat, lon;
        
        while (s) {
            string word;
            if (!getline(s, word, ',' ))
                break;
            if (infoNum == 0) {                     // ID = 0
                ID = word;
            } else if (infoNum == 6) {              // latitude
                stringstream lat_string(word);
                lat_string >> lat;
            } else if (infoNum == 7) {              // longitude
                stringstream lon_string(word);
                lon_string >> lon;
            }
            infoNum++;
        }

        Airport airport = Airport(lat, lon, ID);
        airports[ID] = airport;

        if (!graph_.vertexExists(ID))
            graph_.insertVertex(ID);
    }
    if (!infile.eof())
    {
        cerr << "Error\n";
    }
    
    //graph_.print();
    
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
        
        graph_.insertEdge(sourceID, destID);
        
        // set edge weight as distance between source & dest
        Airport sourceLoc = airports[sourceID];
        Airport destLoc = airports[destID];
        
        
        double lon = destLoc.getLongitude() - sourceLoc.getLongitude();
        double lat = destLoc.getLatitude() - sourceLoc.getLatitude();
        
        double dist = 2 * 6371 *
                (asin(sqrt(pow(sin(lat / 2), 2) + cos(sourceLoc.getLatitude()) * cos(destLoc.getLatitude()) * pow(sin(lon / 2), 2))));
        graph_.setEdgeWeight(sourceID, destID, dist);
        
    }
    //graph_.print();
    
    if (!infile.eof())
    {
        cerr << "Error\n";
    }
}

void ShortestPathFinder::BuildPath(map<string, string> &previous, string &dest, vector<Airport>& path) {
    // Base Case : If j is source

    if (previous[dest] == "*") {
        path.push_back(airports[dest]);
        return;
    }
 
    BuildPath(previous, previous[dest], path);
    path.push_back(airports[dest]);
}

string ShortestPathFinder::closestAirport(map<string, int> distMap, map<string, bool> airportSet) {
    // Initialize min value
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
    for (vector<Airport>::iterator it = path.begin(); it != path.end(); it++) {
        cout << it->getName() << " ";
    }
    cout << endl;
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
        //std::cout << "st " << it->first << std::endl;
        //std::cout << "st " << it->second << std::endl;
        if (it->first != start) {
            distMap[it->first] = INT_MAX;
            airportSet[it->first] = false;
        }
    }
    
    for (int i = 0; i < airports.size(); i++) {
        Vertex curr = closestAirport(distMap, airportSet);
        airportSet[curr] = true;
        
        if (curr == end)
            break;
        
        // iterate through neighbors for all remaining airports
        vector<Vertex> neighbors = graph_.getAdjacent(curr);
        for (Vertex neighbor : neighbors) {
            // get total distance from current airport to neighbor
                // get distance between curr & neighbor and add the distance stored for current
            // if this is less than the current distance stored
            
            if (!airportSet[neighbor]) {
                int dist = graph_.getEdgeWeight(curr, neighbor) + distMap[curr];
                if (dist < distMap[neighbor]) {
                    distMap[neighbor] = dist;
                    previous[neighbor] = curr;
                }
            }
        }
    }
    
    BuildPath(previous, end, path);
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

    std::cout << "BFS Traversal" << std::endl;
    
    for(Traversal::Iterator it = bfs.begin();it != bfs.end(); ++it){
        std::cout << "Airport: " << *it << std::endl;
    }
}
