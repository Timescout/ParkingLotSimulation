
#pragma once

#include <vector>
#include <list>
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
    Lot(/* args */);
    ~Lot();

    void addNode(Node node);
    void addEdge(int firstNodeIndex, int secondNodeIndex, Distance distance);

    void addBuilding(Building building);

    std::list<Node>::iterator getNode(int index);
};