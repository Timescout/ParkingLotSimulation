/*  EventUnitTest.h
    Parking Lot Simulator
    Andrew Bergman

    Unit Test for Event class and EventComparer class.
*/

#include <Event.h>

#include <gtest/gtest.h>

TEST(EventUnitTest, ArgumentedConstructor_Creates_CorrectEvent)
{
    std::list<Car> carList;
    Car stubCar;
    carList.push_back(stubCar);
    TimePoint eventTime = 0;
    EventType eventType = EventType::None;

    Event event(eventTime, carList.begin(), eventType);

    EXPECT_EQ(event.eventTime, eventTime);
    EXPECT_EQ(event.carItr, carList.begin());
    EXPECT_EQ(event.eventType, eventType);
}

TEST(EventComparerUnitTest, CompFirstBeforeSecond_returns_True)
{
    TimePoint firstTime = 0;
    TimePoint secondTime = 1;
    std::list<Car> carList;
    Car stubCar;
    carList.push_back(stubCar);
    Event first(firstTime, carList.begin(), EventType::None);
    Event second(secondTime, carList.begin(), EventType::None);
    EventComparer eventComparer;

    bool firstBeforeSecond = eventComparer.comp(first, second);

    EXPECT_TRUE(firstBeforeSecond);
}

TEST(EventComparerUnitTest, CompFirstAfterSecond_returns_False)
{
    TimePoint firstTime = 1;
    TimePoint secondTime = 0;
    std::list<Car> carList;
    Car stubCar;
    carList.push_back(stubCar);
    Event first(firstTime, carList.begin(), EventType::None);
    Event second(secondTime, carList.begin(), EventType::None);
    EventComparer eventComparer;

    bool firstBeforeSecond = eventComparer.comp(first, second);

    EXPECT_FALSE(firstBeforeSecond);
}