

#include <gtest/gtest.h>

#include <Lot.h>

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