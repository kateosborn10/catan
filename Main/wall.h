/**
  * Derived Class of Building. Creates a QLineF that can be drawn between
  * two nodes to represent a wall.
  */
#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsItem>
#include "node.h"
#include "building.h"

class Wall: public Building
{
public:
    Wall(BuildingType type, Node* from, Node* to);
    QLineF get_wall() {return wall_; }
    bool Equals(Wall* wall);

private:
    Node* from_;
    Node* to_;
    QLineF wall_;
};



#endif // WALL_H
