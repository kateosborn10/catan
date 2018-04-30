#include "wall.h"
#include <QtWidgets>

Wall::Wall(Player* owner, BuildingType type, Node* from, Node* to):
    Building(owner, type)
{
    from_ = from;
    to_ = to;
    player_ = owner;
    color_ = player_->get_color();

    wall_ = QLineF(from_->get_position(), to_->get_position());
}


