#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

#include "Airport.h"
#include "edge.h"
#include "random.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;


/**
 * Represents a graph; used by the GraphTools class.
 *
 * source: Fall 2020 lab_ml
 *
 */
class Graph {
public:
    /**
     * Constructor to create an empty graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     */
    Graph(bool weighted);

    /**
     * Constructor to create an empty graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     * @param directed - specifies whether the graph is directed
     */
    Graph(bool weighted, bool directed);

    /**
     * Constructor to create a random, connected graph.
     * @param weighted - specifies whether the graph is a weighted graph or
     *  not
     * @param numVertices - the number of vertices the graph will have
     * @param seed - a random seed to create the graph with
     */
    Graph(bool weighted, int numVertices, unsigned long seed);

    /**
     * Gets all adjacent vertices to the parameter Airport.
     * @param source - Airport to get neighbors from
     * @return a vector of vertices
     */
    vector<Airport> getAdjacent(Airport source) const;

    /**
     * Returns one Airport in the graph. This function can be used
     *  to find a random Airport with which to start a traversal.
     * @return a Airport from the graph
     */
    Airport getStartingAirport() const;

    /**
     * Gets all vertices in the graph.
     * @return a vector of all vertices in the graph
     */
    vector<Airport> getVertices() const;
    

    /**
     * Gets an edge between two vertices.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return - if exist, return the corresponding edge
     *         - if edge doesn't exist, return Edge()
     */
    Edge getEdge(Airport source, Airport destination) const;

    /**
     * Gets all the edges in the graph.
     * @return a vector of all the edges in the graph
     */
    vector<Edge> getEdges() const;

    /**
     * Checks if the given Airport exists.
     * @return - if Airport exists, true
     *         - if Airport doesn't exist, return false
     */
    bool AirportExists (Airport v) const;

    /**
     * Checks if edge exists between two vertices exists.
     * @return - if Edge exists, true
     *         - if Edge doesn't exist, return false
     */
    bool edgeExists(Airport source, Airport destination) const;

        /**
     * Sets the edge label of the edge between vertices u and v.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return - if edge exists, set the label to the corresponding edge(if not directed, set the reverse one too), return edge with new label
     *         - if edge doesn't exist, return InvalidEdge
     */
        Edge setEdgeLabel(Airport source, Airport destination, string label);

    /**
     * Gets the edge label of the edge between vertices u and v.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return - if edge exists, return edge label
     *         - if edge doesn't exist, return InvalidLabel
     */
    string getEdgeLabel(Airport source, Airport destination) const;

    /**
     * Gets the weight of the edge between two vertices.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return - if edge exists, return edge wright
     *         - if doesn't, return InvalidWeight
     */
    int getEdgeWeight(Airport source, Airport destination) const;

    /**
     * Inserts a new Airport into the graph and initializes its label as "".
     * @param v - the name for the Airport
     */
    void insertAirport(Airport v);

    /**
     * Removes a given Airport from the graph.
     * @param v - the Airport to remove
     * @return - if v exists, return v
     *         - if not, return InvalidAirport;
     */
    Airport removeAirport(Airport v);

    /**
     * Inserts an edge between two vertices.
     * A boolean is returned for use with the random graph generation.
     * Hence, an error is not thrown when it fails to insert an edge.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return whether inserting the edge was successful
     */
    bool insertEdge(Airport source, Airport destination);

    /**
     * Removes the edge between two vertices.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @return - if edge exists, remove it and return removed edge
     *         - if not, return InvalidEdge
     */
    Edge removeEdge(Airport source, Airport destination);

    /**
     * Sets the weight of the edge between two vertices.
     * @param source - one Airport the edge is connected to
     * @param destination - the other Airport the edge is connected to
     * @param weight - the weight to set to the edge
     * @return - if edge exists, set edge weight and return  edge with new weight
     *         - if not, return InvalidEdge
     */
    Edge setEdgeWeight(Airport source, Airport destination, int weight);

    /**
     * Creates a name for snapshots of the graph.
     * @param title - the name to save the snapshots as
     */
    void initSnapshot(string title);

    /**
     * Saves a snapshot of the graph to file.
     * initSnapshot() must be run first.
     */
    void snapshot();

    /**
     * Prints the graph to stdout.
     */
    void print() const;

    /**
     * Saves the graph as a PNG image.
     * @param title - the filename of the PNG image
     */
    void savePNG(string title) const;

    bool isDirected() const;

    void clear();


    const static Airport InvalidAirport;
    const static Edge InvalidEdge;
    const static int InvalidWeight;
    const static string InvalidLabel;

private:
    mutable unordered_map<Airport, unordered_map<Airport, Edge>> adjacency_list;

    bool weighted;
    bool directed;
    Random random;
    int picNum;
    string picName;


    /**
     * Returns whether a given Airport exists in the graph.
     * @param v - the Airport to check
     * @param functionName - the name of the calling function to return
     *  in the event of an error
     */
    bool assertAirportExists(Airport v, string functionName) const;

    /**
     * Returns whether thee edge exists in the graph.
     * @param source - one Airport
     * @param destination - another Airport
     * @param functionName - the name of the calling function to return
     *  in the event of an error
     */
    bool assertEdgeExists(Airport source, Airport destination, string functionName) const;


    /**
     * Prints a graph error and quits the program.
     * The program is exited with a segfault to provide a stack trace.
     * @param message - the error message that is printed
     */
    void error(string message) const;
};
