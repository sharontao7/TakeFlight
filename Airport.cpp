/**
 * @file Airport.cpp
 */

#include <string>

#include "Airport.h"

using namespace std; 

/**
 * Default constructor, sets the latitude and longitude to 0.0 and the name to an empty string
 */
Airport::Airport() : Airport("", "", 0.0, 0.0) { }

/**
 * Constructor
 * @param latitude latitude of the Airport
 * @param longitude longitude of the Airport
 * @param name name of the Airport
 */
Airport::Airport(string ID, string name, double latitude, double longitude) :
    ID_(ID), name_(name), latitude_(latitude), longitude_(longitude) {}

/**
 * overload operator < 
 * @param other the other Airport
 * @return true for smaller, false otherwise
 */
bool Airport::operator<(const Airport &other) const {
    return (latitude_ < other.latitude_ || longitude_ < other.longitude_);
}

/**
 * overload operator ==
 * @param other the other Airport
 * @return true for equal, false otherwise 
 */
bool Airport::operator==(const Airport &other) const {
    return (ID_ == other.ID_ && name_ == other.name_ && latitude_ == other.latitude_ &&
            longitude_ == other.longitude_);
}

/* Getters for private variables */
string Airport::getID() const { return ID_; }

string Airport::getName() const { return name_; }

double Airport::getLatitude() const { return latitude_; }

double Airport::getLongitude() const { return longitude_; }
