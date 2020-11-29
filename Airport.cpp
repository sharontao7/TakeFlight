#include "Airport.h"

#include <string>

Airport::Airport() {
    name_ = "";
    latitude_ = 0.0; 
    longitude_ = 0.0; 
}

Airport::Airport(string name, double latitude, double longitude) {
    name_ = name; 
    latitude_ = latitude;
    longitude_ = longitude; 
}

bool Airport::operator<(const Airport& other) const {
    return (latitude_ < other.latitude_ || longitude_ < other.longitude_);
}

bool Airport::operator==(const Airport& other) const {
    return (latitude_ == other.latitude_ && longitude_ == other.longitude_); 
}

std::string Airport::getName() { return name_; }

void Airport::setName(string name) { name_ = name; }

double Airport::getLatitude() { return latitude_; }

void Airport::setLatitude(double latitude) { latitude_ = latitude; }

double Airport::getLongitude() { return longitude_; }

void Airport::setLongitude(double longitude) { longitude_ = longitude; }