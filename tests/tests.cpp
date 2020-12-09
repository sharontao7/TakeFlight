#define CATCH_CONFIG_MAIN
#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../BFS.h"
#include "../Traversal.h"
#include "../ShortestPathFinder.h"
#include "../Airport.h"

using namespace cs225;

TEST_CASE("BFS maintains the correct point on top", "[weight=0][part=1][part=1a]") {
  //ShortestPathFinder spf("airports_sample.dat", "routes_sample.dat");
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

  bfs.add( Vertex("Madang Airport"));
  bfs.add( Vertex("Port Moresby Jacksons International Airport"));
  bfs.add( Vertex("Mount Hagen Kagamuga Airport"));

  REQUIRE( bfs.peek() == Vertex("Goroka Airport") );
}




