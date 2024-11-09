/*  Simulation.h
    Parking Lot Simulation
    Andrew Bergman

    Defines the Simulation class
*/

#pragma once

#include <Utilities.h>
#include <Event.h>
#include <Car.h>
#include <Building.h>
#include <ConnectingRoad.h>
#include <Strip.h>

#include <queue>
#include <deque>
#include <vector>
#include <list>
#include <ostream>
#include <algorithm>

class Simulation
{
private:

    /// @brief The current time in the simulation.
    TimePoint currentTime_;

    /// @brief The future events list.
    std::priority_queue<Event, std::deque<Event>, EventComparer> futureEventsList_;

    std::list<Car> cars_;

    ///// Simulation Parameters /////
    
    /// @brief Seed for randomly generating Car arrivals.
    int seed_;

    /// @brief How long the simulation will generate new arrivals for.
    TimeLength simulationTime_;

    /// @brief The place where the simulation outputs data. Can be a file, cout, or something else.
    std::ostream* output_;

    /// @brief The target parking lot occupancy. Higher means more cars lower means less cars overall.
    float parkingOccupancy_;

    /// @brief Vector of buildings in the simulation. Buildings may "overlap".
    std::vector<Building> buildings_;

    /// @brief Vector of the Locations of enterances to the Parking lot.
    std::vector<Location> enterances_;

    /// @brief Vector that holds parking strips.
    std::vector<Strip> parkingStrips_;

    int carsInLot;
    
public:
    Simulation();

    void addBuilding(Building building);

    void addEnterance(Location enterance);

    void addParkingStrip(Strip parkingStrip);

    void generateArrivals();

    void simulate();

    void addEvent(Event event);

    /// @brief Finds a parking spot in the parking lot for the given car. Starts looking at the car's current location.
    /// @param car The car that a parking spot is found for.
    /// @return How long the car spent looking for the spot, add to current time to get when the car arrives.
    TimeLength findParkingSpot(Car& car);

    void setSeed(int seed);

    void setRunTime(TimeLength funTime);

    void setAverageDensity(float density);

    void outputParameters();

    void outputCar(Car car);

    void setOutputStream(std::ostream& outputStream);
};