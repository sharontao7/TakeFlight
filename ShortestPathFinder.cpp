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
    
}


void ShortestPathFinder::readAirportData(string fileName) {
    /*
    fstream fout;
    
    // opens an existing csv file or creates a new file.
    fout.open("airports_sample.csv", ios::out | ios::app);
     */
    
    fstream fin;
    
    fin.open(fileName, ios::in);
    
    string line, word, temp;
    
    while (fin >> temp) {
        /* for converting file to CSV
        getline(fin, line);
        stringstream s(line);
        
        while (getline(s, word, ',')) {
            fout << word << ", ";
        }
        
        fout << "\n";*/
        
        getline(fin, line);
        stringstream s(line);
        // std::cout << "line: " << line << std::endl;
        
        int infoNum = 0;
        //string ID;
        string IATA;
        int lat, lon;
        
        while (getline(s, word, ',')) {
            // std::cout << "word: " << word << std::endl;
            if (infoNum == 5) {             // airport IATA (id num == 0)
                //ID = word;
                IATA = word;
            } else if (infoNum == 6) {      // latitude
                stringstream lat_string(word);
                lat_string >> lat;
            } else if (infoNum == 7) {      // longitude
                stringstream lon_string(word);
                lon_string >> lon;
            }
            infoNum++;
        }
        
        //std::cout << "id: " << ID << std::endl;
        airports[IATA] = std::pair<int, int>(lat, lon);
    }
}

void ShortestPathFinder::readRouteData(string fileName) {
    fstream fin;
    
    fin.open(fileName, ios::in);
}
