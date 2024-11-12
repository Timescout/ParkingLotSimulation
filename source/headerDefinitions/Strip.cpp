/*  Strip.cpp
    Andrew Bergman

    Defines the Strip class.
*/

#include <Strip.h>

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
        parkingSpots_[i].distanceFromEnterance1 = (i/2)*ParkingSpot::parkingSpotWidth;
        parkingSpots_[i].distanceFromEnterance2 = ((parkingSpots_.size()-i-1)/2)*ParkingSpot::parkingSpotWidth;
        parkingSpots_[i].position = std::max(xSideLength, ySideLength) == xSideLength ? Location(corner1_.x + parkingSpots_[i].distanceFromEnterance1, corner1_.y) : Location(corner1_.x, corner1_.y+ parkingSpots_[i].distanceFromEnterance1);
    }
}

int Strip::getClosestVacantSpot(Location referencePoint) 
{
    int closest = -1;
    int closestDistance = INT32_MAX;
    for (int i = 0; i < parkingSpots_.size(); i++)
    {
        if (!parkingSpots_[i].occupied and distance(parkingSpots_[i].position, referencePoint) < closestDistance)
        {
            closest = i;
            closestDistance = distance(parkingSpots_[i].position, referencePoint);
        }
    }
    return closest;
}

const int Strip::getNumberParkingSpots() { return parkingSpots_.size(); }

Location Strip::getEnterance1() { return enterance1_; }

void Strip::setEnterance1(Location newEnterance) { enterance1_ = newEnterance; }

Location Strip::getEnterance2() { return enterance2_; }

void Strip::setEnterance2(Location newEnterance) { enterance2_ = newEnterance; }

std::vector<ParkingSpot>::iterator Strip::end() { return parkingSpots_.end(); }

ParkingSpot& Strip::operator[](int index) { return parkingSpots_[index]; }

Location Strip::getCorner1() { return corner1_; }

Location Strip::getCorner2() { return corner2_; }

std::vector<ParkingSpot> Strip::getParkingSpots() { return parkingSpots_; }