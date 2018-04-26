#include "tile.h"

/**
 * @brief Tile::Tile
 * @param polygon
 */
Tile::Tile(QPolygonF polygon, Resource resource_type, int dice_roll_number)
{
    polygon_ = polygon;
    resource_type_ = resource_type;
    dice_roll_number_ = dice_roll_number;
}

QPointF Tile::GetMidPoint(){
    QPointF first_point = polygon_.at(0);
    QPointF mid_point(first_point.rx() + 55 * 0.86602540378, first_point.ry() + 22.5);

    return mid_point;
}
