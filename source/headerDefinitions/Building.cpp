/*  Building.cpp
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class
*/

#include <Building.h>

Building::Building() {}

Building::Building(Location enterence)
{
    addEnterence(enterence);
}

Building::Building(std::vector<Location> enterences)
{
    for (std::vector<Location>::iterator i = enterences.begin(); i != enterences.end(); i++)
    {
        addEnterence(*i);
    }
}

Building::~Building() {}

std::vector<Location> Building::getEntereneces() { return enterences_; }

void Building::addEnterence(Location enterence)
{
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