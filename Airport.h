#pragma once

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

class Airport {
public:
    Airport(); 
    Airport(string name, double latitude, double longitude); 
    
    bool operator<(const Airport& other) const; 
    bool operator==(const Airport& other) const; 

    string getName();
    void setName(string name);

    double getLatitude();
    void setLatitude(double latitude);

    double getLongitude();
    void setLongitude(double longitude);

private:
    string name_;
    double latitude_;
    double longitude_;
};
