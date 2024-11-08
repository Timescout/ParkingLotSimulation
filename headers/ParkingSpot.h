#ifndef PARKING_SPOT
#define PARKING_SPOT

#include <Utilities.h>

struct ParkingSpot
{
    bool occupied;
    TimePoint nextVacantTime;
    Distance distanceFromEnterence1;
    Distance distanceFromEnterence2;

    ParkingSpot();

    /// @brief Tells this Spot that a Car has parked.
    /// @param nextVacant The next time point when this spot will be vacant.
    void park(TimePoint nextVacant);

    /// @brief Tells this Spot that the car parked here has left.
    void depart();

    static constexpr bool defaultOccupied = false;
    static constexpr TimePoint defaultNextVacantTime = 0;
    static constexpr Distance defaultDistanceFromEnterence = 0;
    static constexpr int parkingSpotWidth = 8; // Note parking spots are 8 feet by 18 feet. 
};

#endif