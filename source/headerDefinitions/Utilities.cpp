/*  Utilities.cpp
    Andrew Bergman

    Contains definitions for Utilities objects.
*/

#include <Utilities.h>

constexpr float Location::defaultX;
constexpr float Location::defaultY;

Location::Location() : x(defaultX), y(defaultY) {}

Location::Location(float x, float y) : x(x), y(y) {}

const bool Location::operator==(const Location& other) { return x == other.x && y == other.y; } 

const bool operator==(const Location& first, const Location& second) { return first.x == second.x && first.y == second.y; } // why can't I reuse code here?

Distance distance(Location location1, Location location2)
{
    float a = (location1.x-location2.x);
    float b = (location1.y-location2.y);
    return sqrt(a*a + b*b);
}

Distance taxiDistance(Location location1, Location location2)
{
    return abs(location1.x - location2.x) + abs(location1.y - location2.y);
}