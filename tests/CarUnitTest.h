/*  CarUnitTest.h
    Parking Lot Simulator
    Andrew Bergman

    Unit Test for Car class.
*/

#include <Car.h>

#include <gtest/gtest.h>

TEST(CarUnitTest, DefaultConstructor_Creates_DefaultCar)
{
    Car car;

    EXPECT_EQ(car.currentTime_, car.defaultCurrentTime);
    EXPECT_EQ(car.timeDriven_, car.defaultTimeDriven);
    EXPECT_EQ(car.arrivalTime_, car.defaultArrivalTime);
    EXPECT_EQ(car.shoppingTime_, car.defaultShoppingTime);
}

TEST(CarUnitTest, ArgumentedConstructor_Creates_ArgumentedCar) 
{
    TimePoint testCurrentTime = 0;
    TimePoint testArrivalTime = 1;
    TimeLength testShoppingTime = 1;

    Car car(testCurrentTime, testArrivalTime, testShoppingTime);

    EXPECT_EQ(car.currentTime_, &testCurrentTime);
    EXPECT_EQ(car.timeDriven_, car.defaultTimeDriven);
    EXPECT_EQ(car.arrivalTime_, testArrivalTime);
    EXPECT_EQ(car.shoppingTime_, testShoppingTime);
}

TEST(CarUnitTest, GetCurrentTimeWithoutSettingCurrentTime_Throws_RangeError) 
{
    Car car;

    EXPECT_THROW(car.getCurrentTime(), std::range_error);
}

TEST(CarUnitTest, GetCurrentTimeFromArgumentedConstructor_Gets_CorrectCurrentTime)
{
    TimePoint testCurrentTime = 0;
    TimePoint testArrivalTime = 1;
    TimeLength testShoppingTime = 1;
    Car car(testCurrentTime, testArrivalTime, testShoppingTime);

    TimePoint currentTimeOfCar = car.getCurrentTime();

    EXPECT_EQ(currentTimeOfCar, testCurrentTime);
}

TEST(CarUnitTest, SetCurrentTime_Sets_CurrentTime) 
{
    TimePoint testCurrentTime = 0;
    Car car;

    car.setCurrentTime(testCurrentTime);

    EXPECT_EQ(car.getCurrentTime(), testCurrentTime);
}


TEST(CarUnitTest, GetTimeDriven_Gets_CorrectTimeDriven) 
{
    Car car;

    TimeLength timeDrivenOfCar = car.getTimeDriven();

    EXPECT_EQ(timeDrivenOfCar, car.defaultTimeDriven);
}

TEST(CarUnitTest, GetArrivalTime_Gets_CorrectArrivalTime) 
{
    Car car;

    TimePoint arrivalTimeOfCar = car.getArrivalTime();

    EXPECT_EQ(arrivalTimeOfCar, car.defaultArrivalTime);
}

TEST(CarUnitTest, GetShoppingTime_Gets_CorrectShoppingTime) 
{
    Car car;

    TimeLength shoppingTimeOfCar = car.getShoppingTime();

    EXPECT_EQ(shoppingTimeOfCar, car.defaultShoppingTime);
}

TEST(CarUnitTest, AddTimeDriven_Adds_TimeToTimeDriven) 
{
    Car car;
    TimeLength halfTimeAdded = 5;

    car.addTimeDriven(halfTimeAdded);
    car.addTimeDriven(halfTimeAdded);

    EXPECT_EQ(car.getTimeDriven(), halfTimeAdded + halfTimeAdded);
}