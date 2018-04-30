#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsItem>
#include "node.h"
#include "building.h"

class Wall: public Building
{
public:
    Wall(Player* owner, BuildingType type, Node* from, Node* to);
    QLineF get_wall() {return wall_; }
private:
    Player* player_;
    Node* from_;
    Node* to_;
    QColor color_;
    QLineF wall_;
};

#endif // WALL_H
