#include <iostream>
#include <vector>

#include "ShortestPathFinder.h"
#include "Airport.h"

int main(/* int argc, const char * argv[]*/) {
    // TODO
    
    ShortestPathFinder spf("airports_sample.dat", "routes_sample.dat");
    vector<Airport> path = spf.getShortestPath("1", "2");
    
    for (Airport airport : path) {
        std::cout << "Airport: " << airport.getName() << std::endl;
    }
    
    return 0;
}
