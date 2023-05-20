/*  UtilitiesUnitTest.h
    Parking Lot Simulator
    Andrew Bergman

    Unit Test for Utilities objects.
*/

#include <Utilities.h>

#include <gtest/gtest.h>

TEST(UtilitiesUnitTest, DefaultLocationConstructor_Creates_DefaultLocation)
{
    Location location;

    EXPECT_EQ(location.x, location.defaultX);
    EXPECT_EQ(location.y, location.defaultY);
}

TEST(UtilitiesUnitTest, ArgumentedLocationConstructor_Creates_ArgumentedLocation)
{
    int x = 1;
    int y = 1;
    Location location(x, y);

    EXPECT_EQ(location.x, x);
    EXPECT_EQ(location.y, y);
}

TEST(UtilitiesUnitTest, LocationEqalityCompareisonEqualLocations_Returns_True)
{
    Location location1;
    Location location2;

    bool result = location1 == location2;

    EXPECT_TRUE(result);
}

TEST(UtilitiesUnitTest, LocationEqalityCompareisonUnEqualLocations_Returns_False)
{
    Location location1(0, 0);
    Location location2(1, 1);

    bool result = location1 == location2;

    EXPECT_FALSE(result);
}

TEST(UtilitiesUnitTest, EqalityTwoLocationsCompareisonEqualLocations_Returns_True)
{
    Location location1;
    Location location2;

    bool result = operator==(location1, location2);;

    EXPECT_TRUE(result);
}

TEST(UtilitiesUnitTest, EqalityTwoLocationsCompareisonUnEqualLocations_Returns_False)
{
    Location location1(0, 0);
    Location location2(1, 1);

    bool result = operator==(location1, location2);

    EXPECT_FALSE(result);
}

TEST(UtilitiesUnitTest, DistanceFrom00To50_Equals_5)
{
    Location origin(0,0);
    Location point(5,0);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00To34_Equals_5) 
{
    // We use points that form a pythagorean triple, 3, 4, 5.
    Location origin(0,0);
    Location point(3,4);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00ToNegative34_Equals_5)
{
    // We use points that form a pythagorean triple, 3, 4, 5.
    Location origin(0,0);
    Location point(-3,4);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00To05_Equals_5) 
{
    Location origin(0,0);
    Location point(0,5);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00ToNegative3Negative4_Equals_5) 
{
    // We use points that form a pythagorean triple, 3, 4, 5.
    Location origin(0,0);
    Location point(-3,-4);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00ToNegative50_Equals_5) 
{
    Location origin(0,0);
    Location point(-5,0);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00To3Negative4_Equals_5) 
{
    // We use points that form a pythagorean triple, 3, 4, 5.
    Location origin(0,0);
    Location point(3,-4);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFrom00To0Negative5_Equals_5) 
{
    Location origin(0,0);
    Location point(0,-5);

    Distance distanceFromOriginToPoint = distance(origin, point);

    EXPECT_EQ(distanceFromOriginToPoint, 5);
}

TEST(UtilitiesUnitTest, DistanceFromSelfToSelf_Equals_0)
{
    Location point(0,0);

    Distance distanceFromPointToPoint = distance(point, point);

    EXPECT_EQ(distanceFromPointToPoint, 0);
}