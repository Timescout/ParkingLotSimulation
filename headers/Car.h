/*  Car.h
    Andrew Bergman

    Defines the Car class
*/

#pragma once

#include <Utilities.h>
#include <ParkingSpot.h>

#include <exception>
#include <random>

class Car
{
private:

    // A pointer to the current Time in the Simulation. This is so that the Car can update its metrics.
    TimePoint* currentTime_;

    // How long this car has driven in total
    TimeLength timeDriven_; 

    // When the Car arrived in the Parking Lot
    TimePoint arrivalTime_;

    // How much time this Car will spend shopping
    TimeLength shoppingTime_;

    Location currentLocation_;

    // The location that the car exits the parking lot through. 
    Location endLocation_;

    /// @brief The enterance of the building this car wants to shop at.
    Location buildingEnterance_;

    std::vector<ParkingSpot>::iterator parkingSpotItr_;

    int stripIndex_;

    int spotIndex_;

    float distanceToMeWeight_;

    float distanceToEnteranceWeight_;

    Location arrivalEnterance_;

public:

    ///// Constructors and Deconstructors. /////

    static constexpr TimePoint* defaultCurrentTime = nullptr;
    static constexpr TimeLength defaultTimeDriven = 0;
    static constexpr TimePoint defaultArrivalTime = 0;
    static constexpr TimeLength defaultShoppingTime = 0;
    
    // Default constructor, creates a Car with default values.
    Car();

    // Argumented constructor, creates a Car with the given values.
    Car(TimePoint& currentTime, TimePoint arrivalTime, TimeLength shoppingTime, Location startLocation, Location endLocation, Location buildingEnterance, float distanceToMeWeight, float distanceToEnteranceWeight);

    // Deconstructor. Sets currentTime_ to nullptr.
    ~Car();

    ///// Get and Set functions /////

    // getCurrentTime may throw an excption if no current time is set. This is to prevent dereferencing a nullptr.
    TimePoint getCurrentTime();
    void setCurrentTime(TimePoint& currentTime);

    TimeLength getTimeDriven();
    
    TimePoint getArrivalTime();

    TimeLength getShoppingTime();

    std::vector<ParkingSpot>::iterator& getParkingSpotItr();

    void setParkingSpotItr(std::vector<ParkingSpot>::iterator& newItr);

    Location getCurrentLocation();

    void setCurrentLocation(Location newLocation);

    Location getEndLocation();

    Location getBuildingEnterance();

    int getStripIndex();

    void setStripIndex(int newStripIndex);

    int getSpotIndex();

    void setSpotIndex(int newSpotIndex);

    float getDistanceToMeWeight();

    void setDistanceToMeWeight(float newWeight);

    Location getArrivalEnterance();

    void setArrivalEnterance(Location newEnterance);

    float getDistanceToEnteranceWeight();

    void setDistanceToEnteranceWeight(float newWeight);

    ///// Other class methods /////

    void addTimeDriven(TimeLength timeDriven);

    ///// static member variables /////

    // How fast all of the cars are driving in the parking lot.
    static const int speed = 22; // units are feet per second, 22 feet per second is 15 miles per hour
    

};