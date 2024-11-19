#include <Node.h>

Node::Node(Location position, bool canPark, bool occupied) :
position(position),
canPark(canPark),
occupied(occupied)
{}

Node::Node()
{
    Node(Location(0, 0), false, false);
}

Node::Node(Location position)
{
    Node(position, false, false);
}