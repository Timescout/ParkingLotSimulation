/*  Car.cpp
    Andrew Bergman

    Defines the Car class
*/

#include <Car.h>
#include <stdexcept>

constexpr TimePoint* Car::defaultCurrentTime;
constexpr TimeLength Car::defaultTimeDriven;
constexpr TimePoint Car::defaultArrivalTime;
constexpr TimeLength Car::defaultShoppingTime;

Car::Car() :
    currentTime_(defaultCurrentTime),
    timeDriven_(defaultTimeDriven),
    arrivalTime_(defaultArrivalTime),
    shoppingTime_(defaultShoppingTime)
{}

Car::Car(TimePoint& currentTime, TimePoint arrivalTime, TimeLength shoppingTime, Location startLocation, Location endLocation, Location buildingEnterance, float distanceToMeWeight, float distanceToEnteranceWeight) :
    currentTime_(&currentTime),
    timeDriven_(defaultTimeDriven),
    arrivalTime_(arrivalTime),
    shoppingTime_(shoppingTime),
    currentLocation_(startLocation),
    endLocation_(endLocation),
    buildingEnterance_(buildingEnterance),
    distanceToMeWeight_(distanceToMeWeight),
    distanceToEnteranceWeight_(distanceToEnteranceWeight),
    arrivalEnterance_(startLocation)
{}

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

TimeLength Car::getTimeDriven() { return timeDriven_; }

TimePoint Car::getArrivalTime() { return arrivalTime_; }

TimeLength Car::getShoppingTime() { return shoppingTime_; }

std::vector<ParkingSpot>::iterator& Car::getParkingSpotItr() { return parkingSpotItr_; }

void Car::setParkingSpotItr(std::vector<ParkingSpot>::iterator& newItr) { parkingSpotItr_ = newItr; }

Location Car::getCurrentLocation() { return currentLocation_; }

void Car::setCurrentLocation(Location newLocation) { currentLocation_ = newLocation; }

Location Car::getEndLocation() { return endLocation_; }

Location Car::getBuildingEnterance() { return buildingEnterance_; }

void Car::addTimeDriven(TimeLength timeDriven) { timeDriven_ += timeDriven; }

int Car::getStripIndex() { return stripIndex_; }

void Car::setStripIndex(int newStripIndex) { stripIndex_ = newStripIndex; }

int Car::getSpotIndex() { return spotIndex_; }

void Car::setSpotIndex(int newSpotIndex) { spotIndex_ = newSpotIndex; }

float Car::getDistanceToMeWeight() { return distanceToMeWeight_; }

void Car::setDistanceToMeWeight(float newWeight) { distanceToMeWeight_ = newWeight; }

Location Car::getArrivalEnterance() { return arrivalEnterance_; }

void Car::setArrivalEnterance(Location newEnterance) { arrivalEnterance_ = newEnterance; }

float Car::getDistanceToEnteranceWeight() { return distanceToEnteranceWeight_; }

void Car::setDistanceToEnteranceWeight(float newWeight) { distanceToEnteranceWeight_ = newWeight; }