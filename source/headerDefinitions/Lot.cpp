
#include "Lot.h"

Lot::Lot() {}

Lot::~Lot() {}

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

void Lot::addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance (*distanceFunction)(Location, Location))
{
    // Check that the nodes exist
    if (firstNodeIndex > nodes_.size() or secondNodeIndex > nodes_.size())
    {
        throw std::out_of_range("Invalid node index");
    }

    // Check that we are creating an edge between two different nodes
    if (firstNodeIndex == secondNodeIndex)
    {
        throw std::invalid_argument("Cannot create an edge between a node and itself.");
    }

    auto firstNode = getNode(firstNodeIndex);
    auto secondNode = getNode(secondNodeIndex);
    if (distanceFunction == nullptr)
    {
        throw std::invalid_argument("Distance function pointer cannot be nullptr");
    }
    Distance distance = distanceFunction(firstNode->position, secondNode->position);

    // Check that the edge doesn't already exist
    for (auto i = adjacencyVector_[firstNodeIndex].begin(); i != adjacencyVector_[firstNodeIndex].end(); i++)
    {
        if (i->first == secondNode)
        {
            throw std::invalid_argument("Edge already exists.");
        }
    }

    auto firstEdge = std::pair<std::list<Node>::iterator, Distance>(firstNode, distance);
    adjacencyVector_[secondNodeIndex].push_back(firstEdge);

    auto secondEdge = std::pair<std::list<Node>::iterator, Distance>(secondNode, distance);
    adjacencyVector_[firstNodeIndex].push_back(secondEdge);
}

std::list<Node>::iterator Lot::getNode(int index)
{
    auto itr = nodes_.begin();
    std::advance(itr, index);
    return itr;
}

Distance Lot::getDistance(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex)
{
    auto secondNode = getNode(secondNodeIndex);
    for (auto i = adjacencyVector_[firstNodeIndex].begin(); i != adjacencyVector_[firstNodeIndex].end(); i++)
    {
        if (i->first == secondNode)
        {
            return i->second;
        }
    }
    return -1;
}