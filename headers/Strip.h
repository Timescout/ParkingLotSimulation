/*  Strip.h
    Andrew Bergman

    Defines the Strip class and ParkingSpot struct.
*/

#pragma once

#include <Utilities.h>

#include <vector>
#include <Car.h> // need to know how fast Cars go.
//#include <gtest/gtest.h>



/// @brief A road that has parking spots along the sides of it.
class Strip
{
private:
    // For unit testing.
    //FRIEND_TEST(StripUnitTest, ArgumentedConstructor_Constructs_CorrectObject);
    //FRIEND_TEST(StripUnitTest, SetEnterece2_Sets_Enterece2);
    //FRIEND_TEST(StripUnitTest, End_returns_IteratorToEnd);
    //FRIEND_TEST(StripUnitTest, SetEnterece1_Sets_Enterece1);
    //FRIEND_TEST(StripUnitTest, GetNumberParkingSpots_Gets_CorrectValue);
    //FRIEND_TEST(StripUnitTest, GetClosestVacantSpotEmptyLotEnterence1_Gets_ClosestParkingSpot);
    //FRIEND_TEST(StripUnitTest, GetClosestVacantSpotEmptyLotEnterence2_Gets_ClosestParkingSpot);
    //FRIEND_TEST(StripUnitTest, GetClosestVacantSpotFullLot_Returns_EndIterator);

    Location corner1_;
    Location corner2_;
    Location enterence1_;
    Location enterence2_;

    std::vector<ParkingSpot> parkingSpots_;

public:
    Strip(Location corner1, Location corner2);

    /// @brief Finds the closest vacant spot to a Location.
    /// @param referencePoint Starting point for search.
    /// @param startingTime The time at which the first spot will be checked.
    /// @return An iterator to the Spot found. Will be parkingSpots_.end() if no vacant spots are found.
    int getClosestVacantSpot(Location referencePoint, TimePoint startingTime);

    /// @brief Gets the number of ParkingSpots in this strip.
    /// @return A count of the spots.
    const int getNumberParkingSpots();

    Location getEnterence1();
    void setEnterence1(Location newEnterence);

    Location getEnterence2();
    void setEnterence2(Location newEnterence);

    /// @brief Gets an iterator to the end of the parkingSpots_ vector.
    std::vector<ParkingSpot>::iterator end();

    ParkingSpot& operator[](int index);

    Location getCorner1();
    Location getCorner2();
};