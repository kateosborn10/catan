#include "node.h"

/**
 * @brief Node::Node
 * @param position
 * @param tiles
 */
Node::Node(QPointF position, std::vector<Tile*> tiles)
{
    position_ = position;
    tiles_ = tiles;
}
