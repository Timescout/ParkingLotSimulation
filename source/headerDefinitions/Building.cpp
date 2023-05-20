/*  Building.cpp
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class
*/

#include <Building.h>

Building::Building() {}

Building::Building(Location corner1, Location corner2, Location enterence) :
corner1_(corner1),
corner2_(corner2)
{
    addEnterence(enterence);
}

Building::Building(Location corner1, Location corner2, std::vector<Location> enterences) : 
corner1_(corner1),
corner2_(corner2)
{
    for (std::vector<Location>::iterator i = enterences.begin(); i != enterences.end(); i++)
    {
        addEnterence(*i);
    }
}

Building::~Building() {}

Location Building::getCorner1() { return corner1_; }

Location Building::getCorner2() { return corner2_; }

std::vector<Location> Building::getEntereneces() { return enterences_; }

void Building::addEnterence(Location enterence)
{
    // Check that the enterence is within the square bounds created by the corners.
    if 
    ( 
        ! (std::min(corner1_.x, corner2_.x) <= enterence.x && enterence.x <= std::max(corner1_.x, corner2_.x)) &&
        ! (std::min(corner1_.y, corner2_.y) <= enterence.y && enterence.y <= std::max(corner1_.y, corner2_.y))
    ) 
    {
        throw std::out_of_range("Tried to add enterence outside of Building bounds");
    }

    enterences_.push_back(enterence);
}

Location Building::getClosestEnterence(Location referencePoint)
{
    if (enterences_.size() == 0) { throw std::logic_error("Tried to getClosestEnterence when no enterences exist"); }
    Location closestSoFar = enterences_[0];
    Distance closestDistance = distance(closestSoFar, referencePoint);
    Distance distanceToNextEnterence;
    for (std::vector<Location>::iterator i = (enterences_.begin()++); i != enterences_.end(); i++)
    {
        distanceToNextEnterence = distance(*i, referencePoint);
        if (distanceToNextEnterence < closestDistance)
        {
            closestSoFar = *i;
            closestDistance = distanceToNextEnterence;
        }
    }
    return closestSoFar;
}

Distance Building::getClosestEnterenceDistance(Location referencePoint)
{
    return distance(getClosestEnterence(referencePoint), referencePoint);
}