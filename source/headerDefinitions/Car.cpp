/*  Car.cpp
    Andrew Bergman

    Defines the Car class
*/

#include <Car.h>
#include <stdexcept>

Car::Car() : Car(nullptr, 0, 0, Location(0, 0), Location(0, 0), Location(0, 0), 0, 0) {}

Car::Car(TimePoint& currentTime, TimePoint arrivalTime, TimeLength shoppingTime, Location startLocation, Location endLocation, Location buildingEnterance, float distanceToMeWeight, float distanceToEnteranceWeight)
{
    setCurrentTime(currentTime);
    arrivalTime_ = arrivalTime;
    shoppingTime_ = shoppingTime;
    setArrivalEnterance(startLocation);
    endLocation_ = endLocation;
    buildingEnterance_ = buildingEnterance;
    setDistanceToMeWeight(distanceToMeWeight);
    setDistanceToEnteranceWeight(distanceToEnteranceWeight);
}

Car::~Car()
{
    currentTime_ = nullptr;
}

TimePoint Car::getCurrentTime() 
{
    if (currentTime_ == nullptr) { throw std::range_error("Tried to getCurrentTime without a current Time existing"); }
    return *currentTime_; 
}

void Car::setCurrentTime(TimePoint& currentTime) { currentTime_ = &currentTime; }

TimeLength Car::getTimeDriven() { return totalTimeDriven_; }

TimePoint Car::getArrivalTime() { return arrivalTime_; }

TimeLength Car::getShoppingTime() { return shoppingTime_; }

Location Car::getCurrentLocation() { return currentLocation_; }

void Car::setCurrentLocation(Location newLocation) { currentLocation_ = newLocation; }

Location Car::getEndLocation() { return endLocation_; }

Location Car::getBuildingEnterance() { return buildingEnterance_; }

void Car::addTimeDriven(TimeLength timeDriven) { totalTimeDriven_ += timeDriven; }

float Car::getDistanceToMeWeight() { return distanceToMeWeight_; }

void Car::setDistanceToMeWeight(float newWeight) { distanceToMeWeight_ = newWeight; }

Location Car::getArrivalEnterance() { return arrivalEnterance_; }

void Car::setArrivalEnterance(Location newEnterance) { arrivalEnterance_ = newEnterance; }

float Car::getDistanceToEnteranceWeight() { return distanceToEnteranceWeight_; }

void Car::setDistanceToEnteranceWeight(float newWeight) { distanceToEnteranceWeight_ = newWeight; }

int Car::getSpeed() { return speed_; }

void Car::setSpeed(int newSpeed) { speed_ = newSpeed; }

std::list<Node>::iterator Car::chooseNode(Lot lot)
{
    // Find all parking spots this car can see.
    // 
}

