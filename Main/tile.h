/**
  * Represents the tiles on the catan board. Contain
  * Polygon objects, resource type and integer value of dice roll number
  */

#ifndef TILE_H
#define TILE_H
#include <QPolygonF>
#include "resource.h"


class Tile
{
public:
    Tile(QPolygonF polygon, Resource resource_type, int dice_roll_number);
    QPolygonF get_polygon(){return polygon_;}
    int get_dice_roll_number(){return dice_roll_number_;}
    Resource get_resource_type(){ return resource_type_; }
    QPointF GetMidPoint();
private:
    QPolygonF polygon_;
    Resource resource_type_;
    int dice_roll_number_;
};

#endif // TILE_H
