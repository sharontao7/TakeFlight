#include <iostream>
#include <vector>

#include "ShortestPathFinder.h"
#include "Airport.h"
#include "BFS.h"
#include "Traversal.h"

int main(/* int argc, const char * argv[]*/) {
    // TODO
    
    ShortestPathFinder spf("airports_sample.dat", "routes_sample.dat");
    /*
    vector<Airport> path = spf.getShortestPath("1", "2");
    
    for (Airport airport : path) {
        std::cout << "Airport: " << airport.getName() << std::endl;
    }
    */
    
    /*
    Graph testGraph = Graph(true);
    testGraph.insertVertex("Goroka Airport");
    testGraph.insertVertex("Madang Airport");
    testGraph.insertVertex("Mount Hagen Kagamuga Airport");
    testGraph.insertVertex("Nadzab Airport");
    testGraph.insertVertex("Port Moresby Jacksons International Airport"); 
    testGraph.insertVertex("Wewak International Airport");
    testGraph.insertVertex("Narsarsuaq Airport");

    testGraph.insertEdge("Goroka Airport", "Madang Airport");
    testGraph.insertEdge("Madang Airport", "Wewak International Airport");
    testGraph.insertEdge("Goroka Airport", "Port Moresby Jacksons International Airport");
    testGraph.insertEdge("Port Moresby Jacksons International Airport", "Narsarsuaq Airport");
    testGraph.insertEdge("Goroka Airport", "Mount Hagen Kagamuga Airport");
    testGraph.insertEdge("Mount Hagen Kagamuga Airport", "Nadzab Airport");

    Vertex startingVertex("Goroka Airport");
    BFS bfs(testGraph, startingVertex);

    //bfs.add( Vertex("Madang Airport"));
    //bfs.add( Vertex("Port Moresby Jacksons International Airport"));
    //bfs.add( Vertex("Mount Hagen Kagamuga Airport"));
    for(Traversal::Iterator it = bfs.begin();it != bfs.end(); ++it){
        std::cout << "Airport: " << *it << std::endl;
    }
    
    Traversal::Iterator it = bfs.begin();
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;   
    */
    //std::cout << bfs.pop() << std::endl; 
    //std::cout << bfs.pop() << std::endl; 
    //std::cout << bfs.pop() << std::endl;  

    

   //ShortestPathFinder spf("airport_sample.dat", "routes_sample.dat");
   spf.BFSTraversal("1");
    return 0;
}
