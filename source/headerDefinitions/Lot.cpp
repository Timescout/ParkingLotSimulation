
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
    adjacencyVector_.push_back(std::vector<std::pair<unsigned int, Distance>>());
}

void Lot::addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance (*distanceFunction)(Location, Location))
{
    // Need these for the distance function, and to check that these nodes exist.
    Node firstNode = getNode(firstNodeIndex);
    Node secondNode = getNode(secondNodeIndex);
    Distance distance = distanceFunction(firstNode.position, secondNode.position);

    if (firstNodeIndex == secondNodeIndex)
    {
        throw std::invalid_argument("Cannot create an edge between a node and itself.");
    }

    if (distanceFunction == nullptr)
    {
        throw std::invalid_argument("Distance function pointer cannot be nullptr");
    }

    // Check that the edge doesn't already exist
    for (auto i = adjacencyVector_[firstNodeIndex].begin(); i != adjacencyVector_[firstNodeIndex].end(); i++)
    {
        if (i->first == secondNodeIndex)
        {
            throw std::invalid_argument("Edge already exists.");
        }
    }

    auto firstEdge = std::pair<unsigned int, Distance>(firstNodeIndex, distance);
    adjacencyVector_[secondNodeIndex].push_back(firstEdge);

    auto secondEdge = std::pair<unsigned int, Distance>(secondNodeIndex, distance);
    adjacencyVector_[firstNodeIndex].push_back(secondEdge);
}

Node Lot::getNode(const unsigned int index)
{
    // check that the node exists
    if (index >= nodes_.size())
    {
        throw std::out_of_range("Tried to get node which does not exist.");
    }

    return nodes_[index];
}

Distance Lot::getDistance(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex)
{
    // check that the nodes exist
    if (firstNodeIndex >= nodes_.size() or secondNodeIndex >= nodes_.size())
    {
        throw std::out_of_range("Tried to get distance between nodes that do not exist.");
    }
    for (auto i = adjacencyVector_[firstNodeIndex].begin(); i != adjacencyVector_[firstNodeIndex].end(); i++)
    {
        if (i->first == secondNodeIndex)
        {
            return i->second;
        }
    }
    return -1;
}

nlohmann::json Lot::toJson() 
{
    nlohmann::json value {
        {"Buildings", {}},
        {"Nodes", {}},
        {"AdjacencyValues", {}}
    };

    for (auto i = buildings_.begin(); i != buildings_.end(); i++)
    {
        value.at("Buildings").push_back({});
        auto itr = value.at("Buildings").end();
        itr--;
        std::vector<Location> enterancePositions = i->getEnteraneces();
        for (auto j = enterancePositions.begin(); j != enterancePositions.end(); j++)
        {
            itr->push_back({j->x, j->y});
        }
    }

    auto itr = value.at("Nodes").begin();
    for (auto i = nodes_.begin(); i != nodes_.end(); i++)
    {
        itr->push_back({{i->position.x, i->position.y}, i->canPark, i->occupied});
        itr++;
    }

    for (auto i = adjacencyVector_.begin(); i != adjacencyVector_.end(); i++)
    {
        value.at("AdjacencyValues").push_back({});
        for (auto j = i->begin(); j != i->end(); j++)
        {
            value.at("AdjacencyValues").back().push_back(j->first);
        }
    }

    return value;
}

void Lot::readJson(nlohmann::json file)
{
    // Reset the lot to an empty state.
    buildings_.clear();
    nodes_.clear();
    adjacencyVector_.clear();

    for (auto i = file["Buildings"].begin(); i != file["Buildings"].end(); i++)
    {
        Building building;
        for (auto j = i->begin(); j != i->end(); j++)
        {
            building.addEnterance(Location(j->at(0), j->at(1)));
        }
        buildings_.push_back(building);
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