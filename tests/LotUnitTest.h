

#include <gtest/gtest.h>

#include <Lot.h>

nlohmann::json createLotJson()
{
    nlohmann::json value = 
    R"(
    {
        "Buildings":
        [
            [[0,0]]
        ],
        "Nodes":
        [
            [[1, 1], false, false],
            [[0, 1], true, true]
        ],
        "AdjacencyValues":
        [
            [1],
            [0]
        ]
    }
    )"_json;
    return value;
}

// TEST(LotUnitTest, TESTNAME)
// {

// }

TEST(LotUnitTest, AddEdge_PositiveTest_Success)
{
    Lot lot;
    Node nodeOne;
    Node nodeTwo;
    nodeOne.position = Location(1, 1);
    nodeTwo.position = Location(2, 2);
    lot.addNode(nodeOne);
    lot.addNode(nodeTwo);

    lot.addEdge(0, 1);

    // the distance between node one and node two should use the taxicab distance which should be 2.
    EXPECT_EQ(lot.getDistance(0, 1), 2);
}

TEST(LotUnitTest, AddEdge_SameEdgeTwice_ThrowsError)
{
    Lot lot;
    lot.addNode(Node());
    lot.addNode(Node());

    lot.addEdge(0, 1);
    EXPECT_ANY_THROW(lot.addEdge(0, 1));
}

TEST(LotUnitTest, AddEdge_SameNodeTwice_ThrowsError)
{
    Lot lot;
    lot.addNode(Node());

    EXPECT_ANY_THROW(lot.addEdge(0, 0));
}

TEST(LotUnitTest, AddEdge_NodeDoesntExist_ThrowsError)
{
    Lot lot;
    
    EXPECT_ANY_THROW(lot.addEdge(0, 1));
}

TEST(LotUnitTest, AddEdge_InsideLoop_Works)
{
    Lot lot;
    lot.addNode(Node());
    for (int i = 1; i < 10; i++)
    {
        lot.addNode(Node());
        lot.addEdge(0, i);
    }
}

TEST(LotUnitTest, GetDistance_NodeDoesntExist_ThrowsError)
{
    Lot lot;

    EXPECT_ANY_THROW(lot.getDistance(0, 1));
}

TEST(LotUnitTest, GetDistance_EdgeDoesntExist_ReturnsN1)
{
    Lot lot;
    lot.addNode(Node());
    lot.addNode(Node());

    int value = lot.getDistance(0, 1);

    EXPECT_EQ(value, -1);
}

TEST(LotUnitTest, ReadJson_CreateLotJson_Success)
{
    Lot lot(createLotJson());

    std::vector<Building> buildings = lot.getBuildings();
    Node nodeZero = *lot.getNode(0);
    Node nodeOne = *lot.getNode(1);

    EXPECT_EQ(buildings.size(), 1);
    EXPECT_EQ(buildings[0].getClosestEnterance(Location(0, 0)), Location(0, 0));
    EXPECT_EQ(nodeZero.position, Location(1, 1));
    EXPECT_FALSE(nodeZero.canPark);
    EXPECT_FALSE(nodeZero.occupied);
    EXPECT_EQ(nodeOne.position, Location(0, 1));
    EXPECT_TRUE(nodeOne.canPark);
    EXPECT_TRUE(nodeOne.occupied);
}