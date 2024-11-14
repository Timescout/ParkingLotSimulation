
#pragma once

#include <vector>
#include <Utilities.h>

struct Node
{
    int id;
    bool canPark;
    bool occupied;
    Location position;
    std::vector<std::pair<int, int>> connections;
};