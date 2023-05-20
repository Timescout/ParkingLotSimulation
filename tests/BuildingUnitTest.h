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

    EXPECT_EQ(building.corner1_, Location());
    EXPECT_EQ(building.corner2_, Location());
    EXPECT_EQ(building.enterences_, std::vector<Location>());
}

TEST(BuildingUnitTest, ArgumentedConstructorSingleEnterence_Creates_ArgumentedBuilding)
{
    Location enterence(.5, .5);
    std::vector<Location> enterenceVector {enterence};
    Location corner1(0, 0);
    Location corner2(5, 5);

    Building building(corner1, corner2, enterence);

    EXPECT_EQ(building.corner1_, corner1);
    EXPECT_EQ(building.corner2_, corner2);
    EXPECT_EQ(building.enterences_, enterenceVector);
}

TEST(BuildingUnitTest, ArgumentedConstructorManyEnterences_Creates_ArgumentedBuilding)
{
    Location enterence1(.5, .5);
    Location enterence2(0, 3);
    std::vector<Location> enterenceVector {enterence1, enterence2};
    Location corner1(0, 0);
    Location corner2(5, 5);

    Building building(corner1, corner2, enterenceVector);

    EXPECT_EQ(building.corner1_, corner1);
    EXPECT_EQ(building.corner2_, corner2);
    EXPECT_EQ(building.enterences_, enterenceVector);
}

TEST(BuildingUnitTest, GetCorner1_Gets_CorrectCorner1)
{
    Building building;

    Location corner1OfBuilding = building.getCorner1();

    EXPECT_EQ(corner1OfBuilding, Location());
}

TEST(BuildingUnitTest, GetCorner2_Gets_CorrectCorner2)
{
    Building building;

    Location corner2OfBuilding = building.getCorner2();

    EXPECT_EQ(corner2OfBuilding, Location());
}

TEST(BuildingUnitTest, GetEnterences_Gets_CorrectEntrences)
{
    Building building;

    std::vector<Location> enterencesOfBuilding = building.getEntereneces();

    EXPECT_EQ(enterencesOfBuilding, std::vector<Location>());
}

TEST(BuildingUnitTest, AddEnterenceInBounds_Adds_Enterence)
{
    std::vector<Location> enterences{Location(0, 0), Location(1, 1)};
    Building building(Location(0, 0), Location(5, 5), enterences[0]);

    building.addEnterence(enterences[1]);

    EXPECT_EQ(building.getEntereneces(), enterences);
}

TEST(BuildingUnitTest, AddEnterenceOutOfBounds_Throws_OutOfRangeError)
{
    Building building;

    EXPECT_THROW(building.addEnterence(Location(2, 2)), std::out_of_range);
}

TEST(BuildingUnitTest, GetClosestEnterenceOneEnterence_Gets_ClosestEnterence)
{
    Building building;
    Location enterence(0, 0);
    building.addEnterence(enterence);
    Location referencePoint(10, 10);

    Location closestEnterenceToReferencePoint = building.getClosestEnterence(referencePoint);

    EXPECT_EQ(closestEnterenceToReferencePoint, enterence);
}

TEST(BuildingUnitTest, GetClosestEnterenceTwoEnterences_Gets_ClosestEnterence)
{
    Location corner1OfBuilding(0, 0);
    Location corner2OfBuilding(10, 10);
    std::vector<Location> enterencesToBuilding {Location(0, 0), Location(1, 1)};
    Building building(corner1OfBuilding, corner2OfBuilding, enterencesToBuilding);
    Location referencePoint = Location(2, 2);

    Location closestEnterenceToReferencePoint = building.getClosestEnterence(referencePoint);

    EXPECT_EQ(closestEnterenceToReferencePoint, enterencesToBuilding[1]);
}

TEST(BuildingUnitTest, GetClosestEnterenceNoEnterences_Throws_LogicError)
{
    Building building(Location(0, 0), Location(1, 1), std::vector<Location>());

    EXPECT_THROW(building.getClosestEnterence(Location(0, 0)), std::logic_error);
}

TEST(BuildingUnitTest, GetClosestEnterenceDistanceOneEnterence_Gets_CorrectDistance)
{
    Location enterence(0, 0);
    Building building;
    building.addEnterence(enterence);
    Location referencePoint(10, 10);

    Distance closestEnterenceDistanceToReferencePoint = building.getClosestEnterenceDistance(referencePoint);

    EXPECT_EQ(closestEnterenceDistanceToReferencePoint, distance(enterence, referencePoint));
}

TEST(BuildingUnitTest, GetClosestEnterenceDistanceTwoEnterences_Gets_CorrectDistance)
{
    Location corner1OfBuilding(0, 0);
    Location corner2OfBuilding(10, 10);
    std::vector<Location> enterencesToBuilding {Location(0, 0), Location(1, 1)};
    Building building(corner1OfBuilding, corner2OfBuilding, enterencesToBuilding);
    Location referencePoint = Location(2, 2);

    Distance closestEnterenceDistanceToReferencePoint = building.getClosestEnterenceDistance(referencePoint);

    EXPECT_EQ(closestEnterenceDistanceToReferencePoint, distance(enterencesToBuilding[1], referencePoint));
}