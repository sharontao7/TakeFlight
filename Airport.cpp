#include "Airport.h"

#include <string>

using namespace std; 

/**
 * Default constructor, sets the latitude and longitude to 0.0 and the name to an empty string
 */
Airport::Airport() : Airport(0.0, 0.0, "") { }

/**
 * Constructor
 * @param latitude latitude of the Airport
 * @param longitude longitude of the Airport
 * @param name name of the Airport
 */
Airport::Airport(double latitude, double longitude, string name) : latitude_(latitude), longitude_(longitude),
                                                          name_(name) {}

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
    return (latitude_ == other.latitude_ && longitude_ == other.longitude_ && name_ == other.name_);
}

/* Getters for private variables */
double Airport::getLatitude() const { return latitude_; }

double Airport::getLongitude() const { return longitude_; }

string Airport::getName() const { return name_; }