#include "wall.h"
#include <QtWidgets>

Wall::Wall(Node* from, Node* to, Player* player)
{
    from_ = from->get_position();
    to_ = to->get_position();
    color_ = player->get_color();
    player_ = player;
    wall_ = QLineF(from_, to_);
}


