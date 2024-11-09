/*  Event.cpp
    Parking Lot Simulation
    Andrew Bergman

    Defines Types to manage Events in the simulation.
*/

#include <Event.h>

Event::Event() {}

Event::Event(TimePoint eventTime, std::list<Car>::iterator carItr, EventType type) :
    eventTime(eventTime),
    carItr(carItr),
    eventType(type)
{}

EventComparer::EventComparer() {}

bool EventComparer::comp(Event first, Event second) { return first.eventTime < second.eventTime; }

bool EventComparer::equiv(Event first, Event second) { return first.eventTime == second.eventTime; }

bool EventComparer::operator()(Event first, Event second) { return comp(first, second); }