
#pragma once

#include <vector>
#include <list>
#include <iterator>

#include <Node.h>
#include <Building.h>

#include <nlohmann/json.hpp>

class Lot
{
private:
    /// @brief Where the nodes are held. Since each node has a lot of data which would make access complicated storing this and the graph connections separatly is the way that I've decided to do things. It is a list since in the adjacency vector iterators to specific nodes are used and a list will not invalidate those when adding new nodes.
    std::vector<Node> nodes_; 

    std::vector<Building> buildings_;

    std::vector
    <
        std::vector
        <
            std::pair
            <
                unsigned int, Distance
            >
        >
    > adjacencyVector_;

public:
    Lot();

    Lot(nlohmann::json);

    ~Lot();

    void addNode(Node node);

    /// @brief Add an edge to the lot between two different nodes. This cannot create an edge that already exists. 
    /// @param firstNodeIndex The index of one of the nodes.
    /// @param secondNodeIndex The index of the other node.
    /// @param distanceFunction The distance function used to determine the distance between the two nodes. Default value is the taxi distance defined in utilities.h
    void addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance (*distanceFunction)(Location, Location) = taxiDistance);

    void addBuilding(Building building);

    std::vector<Building> getBuildings();

    Node getNode(const unsigned int index);

    Distance getDistance(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex);

    /// @brief Returns a list of visible nodes from the current node that are currently unoccuped. If nodes are blocked by occuped spaces then they will not be returned from this function.
    /// @param currentPositionIndex Index of the node which this is called from. 
    /// @return A vector of visible empty nodes.
    std::vector<unsigned int> getVisibleEmptyNodes(unsigned int currentPositionIndex);

    /// @brief Returns a list of visible nodes from the current node that are currently unoccuped. If nodes are blocked by occuped spaces then they will not be returned from this function.
    /// @param currentPosition The location this function is called from.
    /// @return A vector of visible empty nodes.
    std::vector<unsigned int> getVisibleEmptyNodes(Location currentPosition);

    nlohmann::json toJson();

    /// @brief Overrites this lot with the one specified by the json file. Destroys all data in this lot.
    /// @param file The json file.
    void readJson(nlohmann::json file);
};