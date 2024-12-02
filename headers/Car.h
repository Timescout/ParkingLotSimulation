/*  Car.h
    Andrew Bergman

    Defines the Car class
*/

#pragma once

#include <Utilities.h>
#include <ParkingSpot.h>
#include <Lot.h>

#include <exception>
#include <random>

class Car
{
private:

    // A pointer to the current Time in the Simulation. This is so that the Car can update its metrics.
    TimePoint* currentTime_;

    Lot* lot_;

    // When the Car arrived in the Parking Lot
    TimePoint arrivalTime_;

    // How much time this Car will spend shopping
    TimeLength shoppingTime_;

    // The location that the car exits the parking lot through. 
    unsigned int exitIndex_;

    unsigned int arrivalIndex_;

    /// @brief The enterance of the building this car wants to shop at.
    Location buildingEnterance_;

    int speed_;

    unsigned int currentLocationIndex_;
public:

    ///// Constructors and Deconstructors. /////
    
    // Default constructor, creates a Car with default values.
    Car();

    // Argumented constructor, creates a Car with the given values.
    Car(TimePoint& currentTime, Lot& lot, TimePoint arrivalTime, TimeLength shoppingTime, unsigned int arrivalIndex, unsigned int exitIndex, int buildingIndex, int buildingEnteranceIndex);

    // Deconstructor. Sets currentTime_ to nullptr.
    ~Car();

    ///// Get and Set functions /////

    // getCurrentTime may throw an excption if no current time is set. This is to prevent dereferencing a nullptr.
    TimePoint getCurrentTime();
    void setCurrentTime(TimePoint& currentTime);

    TimeLength getTimeDriven();
    
    TimePoint getArrivalTime();

    TimeLength getShoppingTime();

    Location getCurrentLocation();

    void setCurrentLocation(Location newLocation);

    unsigned int getEndLocation();

    Location getBuildingEnterance();

    Location getArrivalEnterance();

    void setArrivalEnterance(Location newEnterance);

    int getSpeed();

    void setSpeed(int newSpeed);

    ///// Other class methods /////

    void addTimeDriven(TimeLength timeDriven);

    int evaluate(Node node);

    std::list<Node>::iterator chooseNode(Lot lot);
};