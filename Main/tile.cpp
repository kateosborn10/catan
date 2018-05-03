#include "tile.h"

/**
 * @brief Tile::Tile constructor, sets the polygon of the tile, resource type and dice number.
 * @param polygon
 */
Tile::Tile(QPolygonF polygon, Resource resource_type, int dice_roll_number)
{
    polygon_ = polygon;
    resource_type_ = resource_type;
    dice_roll_number_ = dice_roll_number;
}

/**
 * @brief Tile::GetMidPoint calculates the midpoint of the hex tile for displaying dice roll numbers.
 * @return the midpoint as a QPointF
 */
QPointF Tile::GetMidPoint(){
    QPointF first_point = polygon_.at(0);
    QPointF mid_point(first_point.rx() + 55 * 0.86602540378, first_point.ry() + 22.5);

    return mid_point;
}
