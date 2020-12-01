/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include "Airport.h"

#include <string>
#include <limits.h>

using std::string;

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * Referenced lab_ml Edge class, written by Sean Massung Spring 2012
 */
class Edge {
  public:
    Airport source; // Edge start point
    Airport dest; // Edge end point

    /**
     * Default constructor.
     */
    Edge() : source(Airport()), dest(Airport()), label(""), weight(-1) { }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one Airport the edge is connected to
     * @param v - other Airport the edge is connected to
     */
    Edge(Airport u, Airport v) : source(u), dest(v), label(""), weight(-1) { }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one Airport the edge is connected to
     * @param v - the other Airport it is connected to
     * @param lbl - the edge label
     */
    Edge(Airport u, Airport v, string lbl)
        : source(u), dest(v), label(lbl), weight(-1) { }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one Airport the edge is connected to
     * @param v - the other Airport it is connected to
     * @param w - the weight of the edge
     * @param lbl - the edge label
     */
    Edge(Airport u, Airport v, int w, string lbl)
        : source(u), dest(v), label(lbl), weight(w) { }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const { return weight < other.weight; }

    /**
     * Gets edge label.
     */
    string getLabel() const { return this->label; }

    /**
     * Gets edge weight.
     */
    int getWeight() const { return this->weight; }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const {
        return (this->source == other.source && this->dest == other.dest); 
    }

private:
    string label; // the Edge label
    int weight; // the Edge weight (if a weighted graph)
};
