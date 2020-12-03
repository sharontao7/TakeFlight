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
            if (infoNum == 0) {             // ID = 0
                ID = word;
            } else if (infoNum == 6) {      // latitude
                stringstream lat_string(word);
                lat_string >> lat;
            } else if (infoNum == 7) {      // longitude
                stringstream lon_string(word);
                lon_string >> lon;
            }
            infoNum++;
        }
        
        airports[ID] = std::pair<double, double>(lat, lon);
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
    fstream fin;
    
    fin.open(fileName, ios::in);
    
    string line, word, temp;
    
    while (fin >> temp) {
        getline(fin, line);
        stringstream s(line);
        
        int infoNum = 0;
        //string ID;
        string sourceID, destID;
        
        while (getline(s, word, ',')) {
            if (infoNum == 3) {
                sourceID = word;
            } else if (infoNum == 5) {
                destID = word;
            }
            infoNum++;
        }
        
        graph_.insertEdge(sourceID, destID);
        
        std::pair<double, double> sourceLoc = airports[sourceID];
        std::pair<double, double> destLoc = airports[destID];
        int dist = sqrt(pow(sourceLoc.first - destLoc.first, 2) + pow(sourceLoc.second - destLoc.second, 2));
        graph_.setEdgeWeight(sourceID, destID, dist);
    }
    
    graph_.print();
}
