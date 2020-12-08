#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "ShortestPathFinder.h"
#include "Graph.h"

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
    for (std::pair<string, std::pair<double, double>> airport : airports) {
        std::cout << "Airport: " << airport.first << " " << airport.second.first << " " << airport.second.second << std::endl;
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
        int dist = sqrt(pow(sourceLoc.getLatitude() - destLoc.getLatitude(), 2) + pow(sourceLoc.getLongitude() - destLoc.getLongitude(), 2));
        graph_.setEdgeWeight(sourceID, destID, dist);
    }
    if (!infile.eof())
    {
        cerr << "Error\n";
    }
    
    graph_.print();
}

string ShortestPathFinder::closestAirport(map<string, int> distMap, map<string, bool> airportSet) 
{ 
    // Initialize min value 
    int min = INT_MAX;
    string min_airport;

    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (airportSet[it->first] == false) {
            min = distMap[it->first];
            min_airport = it->first; 
        }
    }
  
    return min_airport; 
} 

vector<Airport> ShortestPathFinder::getShortestPath(Airport start, Airport end) { 

    vector<Airport> ret;
    map<string, int> distMap; 
    map<string, bool> airportSet;

    for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) {
        if (it->first == start.getName()) {
            distMap[it->first] = 0;

        } else {
            distMap[it->first] = INT_MAX;
        }
    }
  
    // Find shortest path for all vertices 
    for (int count = 0; count < airports.size() - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not yet processed
        string closest = closestAirport(distMap, airportSet); 
  
        // Mark the picked vertex as processed 
        airportSet[closest] = true; 
        ret.push_back(airports[closest]);

        // Update dist value of the adjacent vertices of the picked vertex. 
        for (map<string, Airport>::iterator it = airports.begin(); it != airports.end(); it++) { 
            if (!airportSet[closest] && graph_.getEdgeWeight(closest, it->first) && distMap[closest] != INT_MAX 
                && distMap[closest] + graph_.getEdgeWeight(closest, it->first) < distMap[it->first]) {
                    distMap[it->first] = distMap[closest] + graph_.getEdgeWeight(closest, it->first); 
            }
        }
    } 

    return ret;


} 

