/*  Building.h
    Parking Lot Simulator
    Andrew Bergman

    Defines the Building class
*/

#ifndef BUILDING
#define BUILDING

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
    //FRIEND_TEST(BuildingUnitTest, ArgumentedConstructorSingleEnterence_Creates_ArgumentedBuilding);
    //FRIEND_TEST(BuildingUnitTest, ArgumentedConstructorManyEnterences_Creates_ArgumentedBuilding);

    /// @brief A vector of the Locations of enterences to a Building. 
    std::vector<Location> enterences_;
public:
    
    ///// Constructors and deconstructor /////
    
    // Default constructor.
    Building();

    /// @brief Argumented Constructor for Building with one enterence.
    /// @param corner1 Location of the first corner of this Building.
    /// @param corner2 Location of the second corner of this Building.
    /// @param enterence Location of an enterence to this Building.
    Building(Location enterence);

    /// @brief Argumented Constructor for Building with multiple enterences.
    /// @param corner1 Location of the first corner of this Building.
    /// @param corner2 Location of the second corner of this Building.
    /// @param enterences Vector of enterences for this Building
    Building(std::vector<Location> enterences);


    // Deconstructor
    ~Building();

    ///// Get and Set /////

    std::vector<Location> getEntereneces();

    ///// Other class methods /////

    /// @brief Adds an enterence to this Building.
    /// @param enterence The Location to add the enterenece.
    void addEnterence(Location enterence);

    /// @brief Finds the closest enterence to referencePoint that this Building has.
    /// @param referencePoint The point that is considered for finding the closest enterence.
    /// @return The Location of the closest enterence.
    /// @throw std::logic_error If there are no enterences to this Building.
    Location getClosestEnterence(Location referencePoint);

    /// @brief Finds the distance to the closest enternece to referencePoint.
    /// @param referencePoint The point that is considered for finding the closest Distance.
    /// @return The Distance to the closest enterence.
    /// @throw std::logic_error if there are no enterences to this Building.
    Distance getClosestEnterenceDistance(Location referencePoint);
};



#endif