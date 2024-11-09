/*  Strip.cpp
    Andrew Bergman

    Defines the Strip class and ParkingSpot struct.
*/

#include <Strip.h>

constexpr bool ParkingSpot::defaultOccupied;
constexpr TimePoint ParkingSpot::defaultNextVacantTime;
constexpr Distance ParkingSpot::defaultDistanceFromenterance;
constexpr int ParkingSpot::parkingSpotWidth;

ParkingSpot::ParkingSpot() :
    occupied(ParkingSpot::defaultOccupied),
    nextVacantTime(ParkingSpot::defaultNextVacantTime),
    distanceFromenterance1(ParkingSpot::defaultDistanceFromenterance),
    distanceFromenterance2(ParkingSpot::defaultDistanceFromenterance)
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

Strip::Strip(Location corner1, Location corner2) :
    corner1_(corner1),
    corner2_(corner2)
{
    // We have to find the longer side, with ties going to the y axis.
    Distance xSideLength = abs(corner1.x - corner2.x);
    Distance ySideLength = abs(corner1.y - corner2.y);
    int numberSpots;
    if (std::min( ySideLength, xSideLength) >= 52) // 52 gives enough space for a parking spot on each side, plus two lanes to drive in.
    {
        numberSpots = std::max(xSideLength, ySideLength) / ParkingSpot::parkingSpotWidth; // number of spots per side
    }
    parkingSpots_ = std::vector<ParkingSpot>(2 * numberSpots); // one parking spot for each side of the Strip
    for (int i = 0; i < parkingSpots_.size(); i++)
    {
        parkingSpots_[i].distanceFromenterance1 = (i/2)*ParkingSpot::parkingSpotWidth;
        parkingSpots_[i].distanceFromenterance2 = ((parkingSpots_.size()-i)/2)*ParkingSpot::parkingSpotWidth;
    }
}

int Strip::getClosestVacantSpot(Location referencePoint, TimePoint startingTime) // TODO: refactor this code.
{
    bool direction = distance(referencePoint, enterance1_) < distance(referencePoint, enterance2_);
    auto i = direction ? parkingSpots_.begin() : parkingSpots_.end()--;
    int increment = direction ? 1 : -1;
    TimePoint reachesSpot = startingTime;
    for (int counter = 0; counter < parkingSpots_.size(); counter++)
    {
        if (i->nextVacantTime < reachesSpot || !i->occupied) { return counter; }
        reachesSpot += (1/(float)Car::speed) * ParkingSpot::parkingSpotWidth;
        i += direction;
    }
    // No empty spot is found.
    return -1;
}

const int Strip::getNumberParkingSpots() { return parkingSpots_.size(); }

Location Strip::getenterance1() { return enterance1_; }

void Strip::setenterance1(Location newenterance) { enterance1_ = newenterance; }

Location Strip::getenterance2() { return enterance2_; }

void Strip::setenterance2(Location newenterance) { enterance2_ = newenterance; }

std::vector<ParkingSpot>::iterator Strip::end() { return parkingSpots_.end(); }

ParkingSpot& Strip::operator[](int index) { return parkingSpots_[index]; }

Location Strip::getCorner1() { return corner1_; }

Location Strip::getCorner2() { return corner2_; }