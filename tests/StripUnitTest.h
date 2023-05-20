/*  StripUnitTest.h
    Parking Lot Simulator
    Andrew Bergman

    Unit Test for Strip class and ParkingSpot struct.
*/

#include <Strip.h>

#include <gtest/gtest.h>

/*
TEST(ParkingSpotUnitTest, )
{}

TEST(StripUnitTest, )
{}
*/

///// ParkingSpot Unit Tests /////

TEST(ParkingSpotUnitTest, DefaultConstructor_constructs_defaultParkingSpot)
{
    ParkingSpot spot;

    EXPECT_EQ(spot.occupied, ParkingSpot::defaultOccupied);
    EXPECT_EQ(spot.nextVacantTime, ParkingSpot::defaultNextVacantTime);
    EXPECT_EQ(spot.distanceFromEnterence1, ParkingSpot::defaultDistanceFromEnterence);
    EXPECT_EQ(spot.distanceFromEnterence2, ParkingSpot::defaultDistanceFromEnterence);
}

TEST(ParkingSpotUnitTest, Park_sets_correctValues)
{
    ParkingSpot spot;
    TimePoint nextVacantTime = ParkingSpot::defaultOccupied + 1;

    spot.park(nextVacantTime);

    EXPECT_EQ(spot.occupied, true);
    EXPECT_EQ(spot.nextVacantTime, nextVacantTime);
    EXPECT_EQ(spot.distanceFromEnterence1, ParkingSpot::defaultDistanceFromEnterence);
    EXPECT_EQ(spot.distanceFromEnterence2, ParkingSpot::defaultDistanceFromEnterence);
}

TEST(ParkingSpotUnitTest, Depart_Sets_CorrectValues)
{
    ParkingSpot spot;
    TimePoint nextVacantTime = ParkingSpot::defaultOccupied + 1;
    spot.park(nextVacantTime);

    spot.depart();

    EXPECT_EQ(spot.occupied, false);
    EXPECT_EQ(spot.nextVacantTime, nextVacantTime);
    EXPECT_EQ(spot.distanceFromEnterence1, ParkingSpot::defaultDistanceFromEnterence);
    EXPECT_EQ(spot.distanceFromEnterence2, ParkingSpot::defaultDistanceFromEnterence);
}

///// Strip Unit Tests /////

TEST(StripUnitTest, ArgumentedConstructor_Constructs_CorrectObject)
{
    Location corner1 = Location(0, 0);
    Location corner2 = Location( 52, 64);

    Strip strip(corner1, corner2);

    EXPECT_EQ(strip.corner1_, corner1);
    EXPECT_EQ(strip.corner2_, corner2);
    EXPECT_EQ(strip.parkingSpots_.size(), (corner2.y/ParkingSpot::parkingSpotWidth)*2);
    for(int i = 0; i < strip.parkingSpots_.size(); i++)
    {
        EXPECT_EQ(strip.parkingSpots_[i].distanceFromEnterence1, ParkingSpot::parkingSpotWidth*(i/2));
        EXPECT_EQ(strip.parkingSpots_[i].distanceFromEnterence2, corner2.y - ParkingSpot::parkingSpotWidth*(i/2));
    }
}

TEST(StripUnitTest, End_returns_IteratorToEnd)
{
    Strip strip(Location(0, 0), Location(52, 64));

    std::vector<ParkingSpot>::iterator endItr = strip.end();

    EXPECT_EQ(endItr, strip.parkingSpots_.end());
}

TEST(StripUnitTest, GetNumberParkingSpots_Gets_CorrectValue)
{

}

TEST(StripUnitTest, SetEnterece1_Sets_Enterece1)
{}

TEST(StripUnitTest, GetEnterence1_Gets_Enterence1)
{}

TEST(StripUnitTest, SetEnterece2_Sets_Enterece1)
{}

TEST(StripUnitTest, GetClosestVacantSpotEmptyLotEnterence1_Gets_ClosestParkingSpot)
{
    Strip strip(Location(), Location(52, 64));
    strip.setEnterence1(Location(26, 0));
    strip.setEnterence2(Location(26, 64));
    Location referencePoint;

    auto parkingSpotItr = strip.getClosestVacantSpot(referencePoint, 0);

    EXPECT_EQ(parkingSpotItr, strip.parkingSpots_.begin());
}

TEST(StripUnitTest, GetClosestVacantSpotEmptyLotEnterence2_Gets_ClosestParkingSpot)
{
    Strip strip(Location(), Location(52, 64));
    strip.setEnterence1(Location(26, 0));
    strip.setEnterence2(Location(26, 64));
    Location referencePoint(26, 64);

    auto parkingSpotItr = strip.getClosestVacantSpot(referencePoint, 0);

    EXPECT_EQ(parkingSpotItr, strip.parkingSpots_.end()--);
}

TEST(StripUnitTest, GetClosestVacantSpotFullLot_Returns_EndIterator)
{
    Strip strip(Location(), Location(52, 64));
    strip.setEnterence1(Location(26, 0));
    strip.setEnterence2(Location(26, 64));
    Location referencePoint(26, 64);
    for(int i = 0; i < strip.parkingSpots_.size(); i++) { strip.parkingSpots_[i].occupied = true; }

    auto parkingSpotItr = strip.getClosestVacantSpot(referencePoint, 0);

        EXPECT_EQ(parkingSpotItr, strip.parkingSpots_.end());
}

TEST(StripUnitTest, GetEnterence2_Gets_Enterence2)
{}