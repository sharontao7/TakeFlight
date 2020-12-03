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
    /*
    fstream fout;
    
    // opens an existing csv file or creates a new file.
    fout.open(file name goes here, ios::out | ios::app);
    
    fstream fin;
    
    fin.open(fileName, ios::in);
    
    string line, word, temp;
    
    int ind = 1;
    
    while (fin >> temp) {
        getline(fin, line);
        stringstream s(line);
        
        fout << " , " << ind << ", ";
        
        while (getline(s, word, ',')) {
            fout << word << ", ";
        }
        
        fout << "\n";
        ind ++;
    }
    */
    
    fstream fin;
    
    fin.open(fileName, ios::in);
    
    string line, word, temp;
    
    while (fin >> temp) {
        getline(fin, line);
        stringstream s(line);
        
        int infoNum = 0;
        string ID;
        //string IATA;
        double lat, lon;
        
        while (getline(s, word, ',')) {
            if (infoNum == 0) {             // IATA = 4, ID = 0
                ID = word;
                //IATA = word;
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

    graph_.print();
    
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
