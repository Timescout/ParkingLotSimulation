/*  Building.cpp
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class
*/

#include <Building.h>

Building::Building() {}

Building::Building(Location enterance)
{
    addEnterance(enterance);
}

Building::Building(std::vector<Location> enterances)
{
    for (std::vector<Location>::iterator i = enterances.begin(); i != enterances.end(); i++)
    {
        addEnterance(*i);
    }
}

Building::~Building() {}

std::vector<Location> Building::getEnteraneces() { return enterances_; }

void Building::addEnterance(Location enterance)
{
    enterances_.push_back(enterance);
}

Location Building::getClosestEnterance(Location referencePoint)
{
    if (enterances_.size() == 0) { throw std::logic_error("Tried to getClosestEnterance when no enterances exist"); }
    Location closestSoFar = enterances_[0];
    Distance closestDistance = distance(closestSoFar, referencePoint);
    Distance distanceToNextEnterance;
    for (std::vector<Location>::iterator i = (enterances_.begin()++); i != enterances_.end(); i++)
    {
        distanceToNextEnterance = distance(*i, referencePoint);
        if (distanceToNextEnterance < closestDistance)
        {
            closestSoFar = *i;
            closestDistance = distanceToNextEnterance;
        }
    }
    return closestSoFar;
}

Distance Building::getClosestEnteranceDistance(Location referencePoint)
{
    return distance(getClosestEnterance(referencePoint), referencePoint);
}