
#pragma once

#include <vector>
#include <list>
#include <iterator>

#include <Node.h>
#include <Building.h>

class Lot
{
private:
    /// @brief Where the nodes are held. Since each node has a lot of data which would make access complicated storing this and the graph connections separatly is the way that I've decided to do things. It is a list since in the adjacency vector iterators to specific nodes are used and a list will not invalidate those when adding new nodes.
    std::list<Node> nodes_; 

    std::vector<Building> buildings_;

    std::vector
    <
        std::vector
        <
            std::pair
            <
                std::list<Node>::iterator, Distance
            >
        >
    > adjacencyVector_;

public:
    Lot();
    ~Lot();

    void addNode(Node node);

    /// @brief Add an edge to the lot between two different nodes. This cannot create an edge that already exists. 
    /// @param firstNodeIndex The index of one of the nodes.
    /// @param secondNodeIndex The index of the other node.
    /// @param distanceFunction The distance function used to determine the distance between the two nodes. Default value is the taxi distance defined in utilities.h
    void addEdge(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex, Distance (*distanceFunction)(Location, Location) = taxiDistance);

    void addBuilding(Building building);

    std::list<Node>::iterator getNode(int index);

    Distance getDistance(const unsigned int firstNodeIndex, const unsigned int secondNodeIndex);
};