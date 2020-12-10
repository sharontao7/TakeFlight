#include <iostream>
#include <vector>

#include "ShortestPathFinder.h"
#include "Airport.h"
#include "BFS.h"
#include "Traversal.h"
#include "Graph.h"

void printInstructions() {
    cout << endl;
    cout << "Options:" << endl;
    cout << "0 - Quit" << endl;
    cout << "1 - BFS" << endl;
    cout << "2 - Shortest Path (Dijkstra)" << endl;
    cout << "3 - Landmark Path" << endl;
    cout << "4 - Print Graph" << endl;
    cout << "5 - Print Neighbors" << endl;
    cout << "6 - Help" << endl;
    cout << endl;
}

int main(/* int argc, const char * argv[]*/) {
    // TODO
    
    /* // for valgrind testing
    ShortestPathFinder spf("airports.dat", "routes.dat");
    spf.printBFS("1");
    spf.getShortestPath("1", "3");
    spf.getLandmarkPath("1", "5", "2");
    */
    
    int pickData;
    cout << "Enter 1 if you do not wish to use the default data files: ";
    cin >> pickData;
    
    string airportFile, routeFile;
    if (pickData == 1) {                        // ask user to input data files
        cout << "Enter airport file name: ";
        cin >> airportFile;
        cout << "Enter route file name: ";
        cin >> routeFile;
    } else {                                    // use default files
        airportFile = "airports.dat";
        routeFile = "routes.dat";
    }
    
    ShortestPathFinder spf(airportFile, routeFile);
    
    int input = -1;
    printInstructions();
    
    while (input != 0) {
        cout << "Enter action # here: ";
        cin >> input;
        
        if (input == 1) {           // BFS Traversal
            string start;
            cout << "Enter starting airport ID: ";
            cin >> start;
            spf.printBFS(start);
            
        } else if (input == 2) {    // Shortest Path (Dijkstra)
            string start, end;
            cout << "Enter starting airport ID: ";
            cin >> start;
            cout << "Enter destination airport ID: ";
            cin >> end;
            vector<Airport> path = spf.getShortestPath(start, end);
            spf.printPath(path);
            
        } else if (input == 3) {    // Landmark Path
            string start, end, landmark;
            cout << "Enter starting airport ID: ";
            cin >> start;
            cout << "Enter destination airport ID: ";
            cin >> end;
            cout << "Enter landmark airport ID: ";
            cin >> landmark;
            vector<Airport> path = spf.getLandmarkPath(start, end, landmark);
            spf.printPath(path);
            
        } else if (input == 4) {    // Print Graph
            spf.printGraph();
            
        } else if (input == 5) {    // Print Neighbors
            string airportID;
            cout << "Enter desired airport ID: ";
            cin >> airportID;
            spf.printNeighbors(airportID);
            
        } else if (input == 6) {    // Print Instructions
            printInstructions();
            
        } else if (input != 0) {    // Check for valid input
            cout << "Please enter a valid action #." << endl;
        }
    }

    return 0;

}
