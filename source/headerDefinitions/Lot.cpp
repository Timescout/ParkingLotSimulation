
#include "Lot.h"

Lot::Lot() {}

void Lot::addBuilding(Building building)
{
    buildings_.push_back(building);
}

void Lot::addNode(Node node)
{
    nodes_.push_back(node);
    // When a new node is added you need to add an element to the adjacency vector.
    adjacencyVector_.push_back(std::vector<std::pair<std::list<Node>::iterator, Distance>>());
}

void Lot::addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance distance)
{
    // Check that the nodes exist
    if (firstNodeIndex > nodes_.size()-1 or secondNodeIndex > nodes_.size() -1)
    {
        throw std::out_of_range("Invalid node index");
    }

    // As long as you advance by one node index and add it to the adjecency vector for the other this should work.
    auto firstEdge = std::pair<std::list<Node>::iterator, Distance>(getNode(firstNodeIndex), distance);
    adjacencyVector_[secondNodeIndex].push_back(firstEdge);

    auto secondEdge = std::pair<std::list<Node>::iterator, Distance>(getNode(secondNodeIndex), distance);
    adjacencyVector_[firstNodeIndex].push_back(secondEdge);
}

std::list<Node>::iterator Lot::getNode(int index)
{
    auto itr = nodes_.begin();
    std::advance(itr, index);
    return itr;
}