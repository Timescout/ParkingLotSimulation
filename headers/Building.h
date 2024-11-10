/*  Building.h
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class. A Building has enterances which Cars want to park near so that the drivers don't have to walk as far to and from their car.
*/

#pragma once

#include <Utilities.h>

#include <vector>
#include <stdexcept>

class Building
{
private:
    /// @brief A vector of the Locations of enterances to a Building. 
    std::vector<Location> enterances_;
public:
    
    ///// Constructors and deconstructor /////
    
    /// @brief default constructor.
    Building();

    /// @brief Argumented Constructor for Building with one enterance.
    /// @param corner1 Location of the first corner of this Building.
    /// @param corner2 Location of the second corner of this Building.
    /// @param enterance Location of an enterance to this Building.
    Building(Location enterance);

    /// @brief Argumented Constructor for Building with multiple enterances.
    /// @param corner1 Location of the first corner of this Building.
    /// @param corner2 Location of the second corner of this Building.
    /// @param enterances Vector of enterances for this Building
    Building(std::vector<Location> enterances);


    /// @brief Deconstructor
    ~Building();

    ///// Get and Set /////

    std::vector<Location> getEnteraneces();

    ///// Other class methods /////

    /// @brief Adds an enterance to this Building.
    /// @param enterance The Location to add the enterenece.
    void addEnterance(Location enterance);

    /// @brief Finds the closest enterance to the reference point.
    /// @param referencePoint The point that is considered for finding the closest enterance.
    /// @return The Location of the closest enterance.
    /// @throw std::logic_error If there are no enterances to this Building.
    Location getClosestEnterance(Location referencePoint);

    /// @brief Finds the distance to the closest enterance to the reference point.
    /// @param referencePoint The point that is considered for finding the closest Distance.
    /// @return The Distance to the closest enterance.
    /// @throw std::logic_error if there are no enterances to this Building.
    Distance getClosestEnteranceDistance(Location referencePoint);
};