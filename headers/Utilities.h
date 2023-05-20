/*  Utilities.h
    Andrew Bergman

    Contains useful functions, typedefs, and data structures.
    Defines:
        Location struct
        TimePoint
        TimeLength

    Look here sometime: https://www.quantstart.com/articles/Statistical-Distributions-in-C/
*/

#pragma once

#include <cmath>

// location in the simulation space, a cartesian plane (just normal plane)
struct Location
{
    float x, y;

    static constexpr float defaultX = 0;
    static constexpr float defaultY = 0;

    ///// Constructors /////

    // default constructor
    Location();

    // argumented constructor
    Location(float x, float y);

    ///// Operators /////

    const bool operator==(const Location& other); 


};

const bool operator==(const Location& first, const Location& second);

// An aggregate sum of Locations
typedef float Distance;

// pythagorean distance between two points in a cartesean plane
Distance distance(Location location1, Location location2);

Distance taxiDistance(Location location1, Location location2);

// A point in time
typedef float TimePoint;

// A Length of time, not connected to a particular point in time.
typedef float TimeLength;