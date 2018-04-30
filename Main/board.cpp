#include "board.h"
#include <iostream>
Board::Board()
{
    // top row: 3 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0,0)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 2 * side_length_ * cos_theta_,0)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 4* side_length_ * cos_theta_,0)));

    // second row: 4 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + -side_length_ * cos_theta_,  side_length_ + side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + side_length_ * cos_theta_, side_length_ + side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 3 * side_length_ * cos_theta_, side_length_ + side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 5 * side_length_ * cos_theta_, side_length_ + side_length_ * sin_theta_)));

    // third row: 5 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(-2 * side_length_ * cos_theta_, 2 * side_length_ + 2 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0, 2 * side_length_ + 2 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(2 * side_length_ * cos_theta_,  2 * side_length_ + 2 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 4* side_length_ * cos_theta_, 2 * side_length_ + 2 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 6* side_length_ * cos_theta_, 2 * side_length_ + 2 * side_length_ * sin_theta_)));

    // fourth row: 4 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(-side_length_ * cos_theta_,  3* side_length_ + 3 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(side_length_ * cos_theta_,  3* side_length_ + 3 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(3 * side_length_ * cos_theta_,  3* side_length_ + 3 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(5 * side_length_ * cos_theta_,  3* side_length_ + 3 * side_length_ * sin_theta_)));

    // fifth and last row: 3 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0, 4 * side_length_ + 4 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(2 * side_length_ * cos_theta_, 4 * side_length_ + 4 * side_length_ * sin_theta_)));
    polygons_.push_back(QPolygonF(calculateHexPoints(4 * side_length_ * cos_theta_, 4 * side_length_ + 4 * side_length_ * sin_theta_)));

}

const QVector<QPointF> Board::calculateHexPoints(float x, float y) {
    QVector<QPointF> points;
    QPointF p1(x, y);
    QPointF p2(x + side_length_* cos_theta_, y - (side_length_* sin_theta_));
    QPointF p3(x + 2 *side_length_* cos_theta_, y);
    QPointF p4(x + 2 * side_length_ * cos_theta_, y + side_length_);
    QPointF p5(x + side_length_ * cos_theta_, y + side_length_ + side_length_* sin_theta_);
    QPointF p6(x, y + side_length_);

    points.append(p1);
    points.append(p2);
    points.append(p3);
    points.append(p4);
    points.append(p5);
    points.append(p6);

    return QVector<QPointF>(points);
}

