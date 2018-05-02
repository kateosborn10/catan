#include "wall.h"
#include <QtWidgets>
#include <iostream>

Wall::Wall(BuildingType type, Node* from, Node* to):
    Building(type)
{
    from_ = from;
    to_ = to;

    wall_ = QLineF(from_->get_position(), to_->get_position());
}

bool Wall::Equals(Wall* wall){
    std::cout << "Friend operator being called!" << std::endl;
    if(from_ == wall->from_ && to_ == wall->to_)
        return true;
    else if(from_ == wall->to_ && to_ == wall->from_)
        return true;
    else
        return false;
}

