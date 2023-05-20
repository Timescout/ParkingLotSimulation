/*  gtest.cpp
    Parking Lot Simulator
    Andrew Bergman

    Provides main function for testing.
*/

#include <gtest/gtest.h>

// Include all test files
#include <UtilitiesUnitTest.h>
#include <BuildingUnitTest.h>
#include <StripUnitTest.h>
#include <CarUnitTest.h>
#include <EventUnitTest.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}