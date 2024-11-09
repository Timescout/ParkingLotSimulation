/*  BuildingUnitTest.h
    Parking Lot Simulator
    Andrew Bergman

    Unit Test for Building class.
*/

#include <Building.h>

#include <gtest/gtest.h>

TEST(BuildingUnitTest, DefaultConstructor_Creates_DefaultBuilding)
{
    Building building;


    EXPECT_EQ(building.getEnteraneces(), std::vector<Location>());
}

TEST(BuildingUnitTest, ArgumentedConstructorSingleEnterance_Creates_ArgumentedBuilding)
{
    Location enterance(.5, .5);
    std::vector<Location> enteranceVector {enterance};

    Building building(enterance);

    EXPECT_EQ(building.getEnteraneces(), enteranceVector);
}

TEST(BuildingUnitTest, ArgumentedConstructorManyEnterances_Creates_ArgumentedBuilding)
{
    Location enterance1(.5, .5);
    Location enterance2(0, 3);
    std::vector<Location> enteranceVector {enterance1, enterance2};

    Building building(enteranceVector);

    EXPECT_EQ(building.getEnteraneces(), enteranceVector);
}

// Depreciated; buildings no longer have corners.
// TEST(BuildingUnitTest, GetCorner1_Gets_CorrectCorner1)
// {
//     Building building;

//     Location corner1OfBuilding = building.getCorner1();

//     EXPECT_EQ(corner1OfBuilding, Location());
// }

// TEST(BuildingUnitTest, GetCorner2_Gets_CorrectCorner2)
// {
//     Building building;

//     Location corner2OfBuilding = building.getCorner2();

//     EXPECT_EQ(corner2OfBuilding, Location());
// }

TEST(BuildingUnitTest, GetEnterances_Gets_CorrectEntrences)
{
    Building building;

    std::vector<Location> enterancesOfBuilding = building.getEnteraneces();

    EXPECT_EQ(enterancesOfBuilding, std::vector<Location>());
}

TEST(BuildingUnitTest, AddEnteranceInBounds_Adds_Enterance)
{
    std::vector<Location> enterances{Location(0, 0), Location(1, 1)};
    Building building(enterances[0]);

    building.addEnterance(enterances[1]);

    EXPECT_EQ(building.getEnteraneces(), enterances);
}

// Depreciated; Buildings no longer have corners.
// TEST(BuildingUnitTest, AddEnteranceOutOfBounds_Throws_OutOfRangeError)
// {
//     Building building;

//     EXPECT_THROW(building.addEnterance(Location(2, 2)), std::out_of_range);
// }

TEST(BuildingUnitTest, GetClosestEnteranceOneEnterance_Gets_ClosestEnterance)
{
    Building building;
    Location enterance(0, 0);
    building.addEnterance(enterance);
    Location referencePoint(10, 10);

    Location closestEnteranceToReferencePoint = building.getClosestEnterance(referencePoint);

    EXPECT_EQ(closestEnteranceToReferencePoint, enterance);
}

TEST(BuildingUnitTest, GetClosestEnteranceTwoEnterances_Gets_ClosestEnterance)
{
    std::vector<Location> enterancesToBuilding {Location(0, 0), Location(1, 1)};
    Building building(enterancesToBuilding);
    Location referencePoint(2, 2);

    Location closestEnteranceToReferencePoint = building.getClosestEnterance(referencePoint);

    EXPECT_EQ(closestEnteranceToReferencePoint, enterancesToBuilding[1]);
}

TEST(BuildingUnitTest, GetClosestEnteranceNoEnterances_Throws_LogicError)
{
    Building building;
    Location referencePoint(0,0);

    EXPECT_THROW(building.getClosestEnterance(referencePoint), std::logic_error);
}

TEST(BuildingUnitTest, GetClosestEnteranceDistanceOneEnterance_Gets_CorrectDistance)
{
    Location enterance(0, 0);
    Building building;
    building.addEnterance(enterance);
    Location referencePoint(10, 10);

    Distance closestEnteranceDistanceToReferencePoint = building.getClosestEnteranceDistance(referencePoint);

    EXPECT_EQ(closestEnteranceDistanceToReferencePoint, distance(enterance, referencePoint));
}

TEST(BuildingUnitTest, GetClosestEnteranceDistanceTwoEnterances_Gets_CorrectDistance)
{
    std::vector<Location> enterancesToBuilding {Location(0, 0), Location(1, 1)};
    Building building(enterancesToBuilding);
    Location referencePoint = Location(2, 2);

    Distance closestEnteranceDistanceToReferencePoint = building.getClosestEnteranceDistance(referencePoint);

    EXPECT_EQ(closestEnteranceDistanceToReferencePoint, distance(enterancesToBuilding[1], referencePoint));
}