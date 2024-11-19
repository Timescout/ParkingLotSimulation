
#pragma once

#include <vector>
#include <Utilities.h>

struct Node
{
    bool canPark;
    bool occupied;
    Location position;

    Node();
    Node(Location position);
    Node(Location position, bool canPark, bool occupied);
};
