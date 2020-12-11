#define CATCH_CONFIG_MAIN
#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../ShortestPathFinder.h"
#include "../Airport.h"
/*
using namespace cs225;

Graph getTestGraph(){
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
  return testGraph;
}

Graph getSampleTestGraph(){
  ShortestPathFinder spf("airports_sample.dat", "routes_sample.dat");
  return spf.getGraph();
}

TEST_CASE("BFS maintains the correct point on top", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getTestGraph();

  Vertex startingVertex("Goroka Airport");
  BFS bfs(testGraph, startingVertex);

  bfs.add( Vertex("Madang Airport"));
  bfs.add( Vertex("Port Moresby Jacksons International Airport"));
  bfs.add( Vertex("Mount Hagen Kagamuga Airport"));

  REQUIRE( bfs.peek() == Vertex("Goroka Airport") );
}

TEST_CASE("BFS maintains the BFS ordering", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getTestGraph();

  Vertex startingVertex("Goroka Airport");
  BFS bfs(testGraph, startingVertex);

  bfs.add( Vertex("Madang Airport"));
  bfs.add( Vertex("Port Moresby Jacksons International Airport"));
  bfs.add( Vertex("Mount Hagen Kagamuga Airport"));

  REQUIRE( bfs.pop() == Vertex("Goroka Airport") );
  REQUIRE( bfs.pop() == Vertex("Madang Airport") );
  REQUIRE( bfs.pop() == Vertex("Port Moresby Jacksons International Airport") );
  REQUIRE( bfs.pop() == Vertex("Mount Hagen Kagamuga Airport") );
}

TEST_CASE("BFS iterator visits all points in the correct order", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getTestGraph();

  Vertex startingVertex("Goroka Airport");
  BFS bfs(testGraph, startingVertex);

  Traversal::Iterator it = bfs.begin();
  REQUIRE( *it == startingVertex );
  ++it;
  REQUIRE( *it == "Madang Airport");
  ++it;
  REQUIRE( *it == "Port Moresby Jacksons International Airport");
  ++it;
  REQUIRE( *it == "Mount Hagen Kagamuga Airport");
  ++it;
  REQUIRE( *it == "Wewak International Airport");
  ++it;
  REQUIRE( *it == "Narsarsuaq Airport");
  ++it;
  REQUIRE( *it == "Nadzab Airport");
}

TEST_CASE("BFS iterator visits all points in the correct order: sample data graph starting point = 1", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getSampleTestGraph();

  Vertex startingVertex("1");
  BFS bfs(testGraph, startingVertex);

  Traversal::Iterator it = bfs.begin();
  REQUIRE( *it == startingVertex );
  ++it;
  REQUIRE( *it == "2");
  ++it;
  REQUIRE( *it == "4");
  ++it;
  REQUIRE( *it == "3");
}

TEST_CASE("BFS iterator visits all points in the correct order: sample data graph starting point = 2", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getSampleTestGraph();

  Vertex startingVertex("2");
  BFS bfs(testGraph, startingVertex);

  Traversal::Iterator it = bfs.begin();
  REQUIRE( *it == startingVertex );
  ++it;
  REQUIRE( *it == "4");
  ++it;
  REQUIRE( *it == "3");
  ++it;
  REQUIRE( *it == "1");
}

TEST_CASE("BFS iterator visits all points in the correct order: sample data graph starting point = 4", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getSampleTestGraph();

  Vertex startingVertex("4");
  BFS bfs(testGraph, startingVertex);

  Traversal::Iterator it = bfs.begin();
  REQUIRE( *it == startingVertex );
  ++it;
  REQUIRE( *it == "2");
  ++it;
  REQUIRE( *it == "1");
  ++it;
  REQUIRE( *it == "3");
}

TEST_CASE("BFS iterator visits all points in the correct order: sample data graph starting point = 3", "[weight=0][part=1][part=1a]") {
  Graph testGraph = getSampleTestGraph();

  Vertex startingVertex("3");
  BFS bfs(testGraph, startingVertex);

  Traversal::Iterator it = bfs.begin();
  REQUIRE( *it == startingVertex );
  ++it;
}

*/

