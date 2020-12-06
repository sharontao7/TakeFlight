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
class Airport {
    public: 
        Airport(); 
        Airport(double latitude, double longitude, string name); 

        bool operator<(const Airport &other) const; 
        bool operator==(const Airport &other) const; 

        double getLatitude() const; 
        double getLongitude() const;
        string getName() const; 

    private: 
        double latitude_; 
        double longitude_; 
        string name_; 
}; 

/**
 * overload operator <<
 * prints out an Airport
 * @param out output stream
 * @param airport the Airport to print
 * @return output stream
 */
inline std::ostream &operator<<(std::ostream &out, Airport const &airport)
{
    out << airport.getName() << ": " << airport.getLatitude() << ", " << airport.getLongitude();
    return out;
}; 

   