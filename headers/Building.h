/*  Building.h
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class. A Building has enterances which Cars want to park near so that the drivers don't have to walk as far to and from their car.
*/

#pragma once

#include <Utilities.h>

#include <vector>
#include <exception>
#include <stdexcept>
//#include <gtest/gtest.h>

class Building
{
private:

    // For testing Constructors
    //FRIEND_TEST(BuildingUnitTest, DefaultConstructor_Creates_DefaultBuilding);
    //FRIEND_TEST(BuildingUnitTest, ArgumentedConstructorSingleenterance_Creates_ArgumentedBuilding);
    //FRIEND_TEST(BuildingUnitTest, ArgumentedConstructorManyenterances_Creates_ArgumentedBuilding);

    /// @brief A vector of the Locations of enterances to a Building. 
    std::vector<Location> enterances_;
public:
    
    ///// Constructors and deconstructor /////
    
    // Default constructor.
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


    // Deconstructor
    ~Building();

    ///// Get and Set /////

    std::vector<Location> getEntereneces();

    ///// Other class methods /////

    /// @brief Adds an enterance to this Building.
    /// @param enterance The Location to add the enterenece.
    void addenterance(Location enterance);

    /// @brief Finds the closest enterance to referencePoint that this Building has.
    /// @param referencePoint The point that is considered for finding the closest enterance.
    /// @return The Location of the closest enterance.
    /// @throw std::logic_error If there are no enterances to this Building.
    Location getClosestenterance(Location referencePoint);

    /// @brief Finds the distance to the closest enternece to referencePoint.
    /// @param referencePoint The point that is considered for finding the closest Distance.
    /// @return The Distance to the closest enterance.
    /// @throw std::logic_error if there are no enterances to this Building.
    Distance getClosestenteranceDistance(Location referencePoint);
};