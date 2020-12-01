#pragma once

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 Data set variables:
 Airport ID - unique OpenFlights identifier
 Name - name of airport
 City - where airport is located
 Country - where airport is located
 IATA Code
 ICAO Code
 Latitude - decimal degrees to six sig figs (negative = South, positive = North)
 Longitude - decimal degrees to six sig figs (negative = West, positive = East)
 Altitude - in ft.
 Timezone - offset from UTC
 DST - daylight savings time
 Tz Database Timezone - in tz format
 Type - airport type (airport, train station, ferry port, unknown)
 Source - data source
 */

/**
 * Simple Airport class containing a public double 'latitude' and 'longitude' to represent 2D points 
 * on a map. Also contains a public string 'name' to represent the name of the Airport. 
 */
struct Airport {
    double latitude_; 
    double longitude_; 
    string name_; 

    /**
     * Default constructor, sets the latitude and longitude to 0.0 and the name to an empty string
     */
    Airport() : Airport(0.0, 0.0, "") { }

    /**
     * Constructor
     * @param latitude latitude of the Airport
     * @param longitude longitude of the Airport
     * @param name name of the Airport
     */
    Airport(double latitude, double longitude, string name) : latitude_(latitude), longitude_(longitude), 
        name_(name) { }

    /**
     * overload operator < 
     * @param other the other Airport
     * @return true for smaller, false otherwise
     */
    bool operator<(const Airport& other) const {
        return (latitude_ < other.latitude_ || longitude_ < other.longitude_); 
    }

    /**
     * overload operator ==
     * @param other the other Airport
     * @return true for equal, false otherwise 
     */
    bool operator==(const Airport& other) const {
        return (latitude_ == other.latitude_ && longitude_ == other.longitude_ && name_ == other.name_); 
    }
}; 

/**
 * overload operator <<
 * prints out an Airport
 * @param out output stream
 * @param airport the Airport to print
 * @return output stream
 */
inline std::ostream& operator<<(std::ostream& out, Airport const& airport) {
    out << airport.name_ << ": " << airport.latitude_ << ", " << airport.longitude_; 
    return out; 
}