#include <ParkingSpot.h>

constexpr bool ParkingSpot::defaultOccupied;
constexpr TimePoint ParkingSpot::defaultNextVacantTime;
constexpr Distance ParkingSpot::defaultDistanceFromEnterance;
constexpr int ParkingSpot::parkingSpotWidth;

ParkingSpot::ParkingSpot() :
    occupied(ParkingSpot::defaultOccupied),
    nextVacantTime(ParkingSpot::defaultNextVacantTime),
    distanceFromEnterance1(ParkingSpot::defaultDistanceFromEnterance),
    distanceFromEnterance2(ParkingSpot::defaultDistanceFromEnterance)
{}

void ParkingSpot::park(TimePoint nextVacant)
{
    occupied = true;
    nextVacantTime = nextVacant;
}

void ParkingSpot::depart()
{
    occupied = false;
}