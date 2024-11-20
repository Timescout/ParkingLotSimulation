
#include "Lot.h"

Lot::Lot() {}

Lot::Lot(nlohmann::json file)
{
    readJson(file);
}

Lot::~Lot() {}

void Lot::addBuilding(Building building)
{
    buildings_.push_back(building);
}

std::vector<Building> Lot::getBuildings()
{
    return buildings_;
}

void Lot::addNode(Node node)
{
    nodes_.push_back(node);
    // When a new node is added you need to add an element to the adjacency vector.
    adjacencyVector_.push_back(std::vector<std::pair<std::list<Node>::iterator, Distance>>());
}

void Lot::addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance (*distanceFunction)(Location, Location))
{
    auto firstNode = getNode(firstNodeIndex);
    auto secondNode = getNode(secondNodeIndex);

    // Check that we are creating an edge between two different nodes
    if (firstNodeIndex == secondNodeIndex)
    {
        throw std::invalid_argument("Cannot create an edge between a node and itself.");
    }

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

std::list<Node>::iterator Lot::getNode(const unsigned int index)
{
    // check that the node exists
    if (index > nodes_.size())
    {
        throw std::out_of_range("Tried to get node which does not exist.");
    }

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

nlohmann::json Lot::toJson() 
{
    return nlohmann::json();
}

void Lot::readJson(nlohmann::json file)
{
    // Reset the lot to an empty state.
    buildings_.clear();
    nodes_.clear();
    adjacencyVector_.clear();

    for (auto i = file["Buildings"].begin(); i != file["Buildings"].end(); i++)
    {
        buildings_.push_back(Building(Location(i->at(0), i->at(1))));
    }

    for (auto i = file["Nodes"].begin(); i != file["Nodes"].end(); i++)
    {
        addNode(Node(Location(i->at(0).at(0), i->at(0).at(1)), i->at(1), i->at(2)));
    }

    for (int i = 0; i < file["AdjacencyValues"].size(); i++) 
    {
        for (int j = 0; j < file["AdjacencyValues"][i].size(); j++)
        {
            if (getDistance(i, file["AdjacencyValues"][i][j]) == -1)
            {
                addEdge(i, file["AdjacencyValues"][i][j]);
            }
        }
    }
}