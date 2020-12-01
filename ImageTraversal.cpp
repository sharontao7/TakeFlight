#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Graph.h"

#include "ImageTraversal.h"


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  isAtEnd_ = true;
}

/**
 * Custom iterator constructor.
 */
ImageTraversal::Iterator::Iterator(Graph graph, Vertex start, ImageTraversal* traversal) {
    graph_ = graph;
    start_ = start;
    traversal_ = traversal;
    isAtEnd_ = false;
    //need to resolve Vertex vs Airport Issue
    current_ = traversal_->peek();
    for(unsigned x = 0; x < graph.getVertices().size(); x++){
        Vertex currVert = graph.getVertices().at(x);
        visited.insert(pair<Vertex, bool>(currVert, false));
    }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traversal_->empty()){
    isAtEnd_ = true;
    return *this;
  } else {
    if(!traversal_->empty()){
      traversal_->pop();
      visited[current_] = true;
    }

    //get neighbour vertices from current vertex
    vector<Vertex> neighbours = graph_.getAdjacent(current_);

    //pop the visited vertices from the traversal and make the last visited vertice our current vertex to check the neighbours of
    //while the traversal is not empty and we are the vertex at the front of the traversal is visited pop the front element of the traversal 
    //and make that our current element
    while(!traversal_->empty() && visited[traversal_->peek()]){
      current_ = traversal_->pop();
    }
    
    //check if the neighbour vertex has not been visited, add to the traversal if it hasn't
    for(int i = 0; i < (int)neighbours.size(); i++){
      Vertex currVert = neighbours.at(i);
      map<Vertex,bool>::iterator it = visited.find(currVert);
      if(it != visited.end()){
        traversal_->add(currVert);
      }
    }

    //if the traversal is not empty update the current element to the front element of the traversal
    if(!traversal_->empty()){
      current_ = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Vertex ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisIsEmpty = false;
  bool otherIsEmpty = false;
  if(traversal_ == nullptr || traversal_->empty()){
    thisIsEmpty = true;
  }
  if(other.traversal_ == nullptr ||other.traversal_->empty()){
    otherIsEmpty = true;
  }
  if(thisIsEmpty == otherIsEmpty){
    return false;
  } else {
    return true;
  }
}

