/*  Building.cpp
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class
*/

#include <Building.h>

Building::Building() {}

Building::Building(Location enterance)
{
    addenterance(enterance);
}

Building::Building(std::vector<Location> enterances)
{
    for (std::vector<Location>::iterator i = enterances.begin(); i != enterances.end(); i++)
    {
        addenterance(*i);
    }
}

Building::~Building() {}

std::vector<Location> Building::getEntereneces() { return enterances_; }

void Building::addenterance(Location enterance)
{
    enterances_.push_back(enterance);
}

Location Building::getClosestenterance(Location referencePoint)
{
    if (enterances_.size() == 0) { throw std::logic_error("Tried to getClosestenterance when no enterances exist"); }
    Location closestSoFar = enterances_[0];
    Distance closestDistance = distance(closestSoFar, referencePoint);
    Distance distanceToNextenterance;
    for (std::vector<Location>::iterator i = (enterances_.begin()++); i != enterances_.end(); i++)
    {
        distanceToNextenterance = distance(*i, referencePoint);
        if (distanceToNextenterance < closestDistance)
        {
            closestSoFar = *i;
            closestDistance = distanceToNextenterance;
        }
    }
    return closestSoFar;
}

Distance Building::getClosestenteranceDistance(Location referencePoint)
{
    return distance(getClosestenterance(referencePoint), referencePoint);
}