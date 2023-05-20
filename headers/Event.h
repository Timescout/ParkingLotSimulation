/*  Event.h
    Parking Lot Simulation
    Andrew Bergman

    Defines Types to manage Events in the simulation.
*/

#pragma once

#include <Car.h>

#include <list>

/// @brief Enum that defines Event Types
enum EventType
{
    None,
    Arrive,
    Park,
    Depart
};

struct Event 
{
    /// @brief When the Event occurs.
    TimePoint eventTime;

    /// @brief An iterator to the Car that this event is attached to.
    std::list<Car>::iterator carItr;

    /// @brief The type of Event this event is.
    EventType eventType;

    Event();

    /// @brief Argumented constructor.
    /// @param eventTime When this Event occurs.
    /// @param car The car that this Event happens to. 
    /// @param type The type of Event.
    Event(TimePoint eventTime, std::list<Car>::iterator carItr, EventType type);
};

/// @brief A class that can compare Events.
class EventComparer
{
public:

    EventComparer();

    /// @brief Evaluates whether the first Event happens after the second Event.
    /// @param first The first Event.
    /// @param second The second Event
    /// @return False if first happens after second. True otherwise.
    bool comp(Event first, Event second);

    /// @brief Evaluates if two events are equivilant
    /// @param first The first Event.
    /// @param second The second Event
    /// @return If the two Events are equivilant or not.
    bool equiv(Event first, Event second);

    bool operator()(Event first, Event second);
};