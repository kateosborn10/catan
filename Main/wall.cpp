#include "wall.h"
#include <QtWidgets>
#include <iostream>

/**
 * @brief Wall::Wall constructor for derived Building class Wall
 * encapsulates a wall with two nodes and a QLineF
 * @param type will always be Wall.
 * @param from is one end of the wall
 * @param to is the other end of the wall
 */
Wall::Wall(BuildingType type, Node* from, Node* to):
    Building(type)
{
    from_ = from;
    to_ = to;

    wall_ = QLineF(from_->get_position(), to_->get_position());
}

/**
 * @brief Wall::Equals checks if two walls are the same. Used to verify valid walls by game.
 * @param wall the other wall to test against
 * @return true if the two walls are the same.
 */
bool Wall::Equals(Wall* wall){
    if(from_ == wall->from_ && to_ == wall->to_)
        return true;
    else if(from_ == wall->to_ && to_ == wall->from_)
        return true;
    else
        return false;
}

