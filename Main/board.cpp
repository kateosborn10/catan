#include "board.h"
#include <iostream>
Board::Board()
{
    // top row: 3 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0,0)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 2 * side_length_ * cos_theta,0)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 4* side_length_ * cos_theta,0)));

    // second row: 4 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + -side_length_ * cos_theta,  side_length_ + side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + side_length_ * cos_theta, side_length_ + side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 3 * side_length_ * cos_theta, side_length_ + side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 5 * side_length_ * cos_theta, side_length_ + side_length_ * sin_theta)));

    // third row: 5 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(-2 * side_length_ * cos_theta, 2 * side_length_ + 2 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0, 2 * side_length_ + 2 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(2 * side_length_ * cos_theta,  2 * side_length_ + 2 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 4* side_length_ * cos_theta, 2 * side_length_ + 2 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(0 + 6* side_length_ * cos_theta, 2 * side_length_ + 2 * side_length_ * sin_theta)));

    // fourth row: 4 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(-side_length_ * cos_theta,  3* side_length_ + 3 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(side_length_ * cos_theta,  3* side_length_ + 3 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(3 * side_length_ * cos_theta,  3* side_length_ + 3 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(5 * side_length_ * cos_theta,  3* side_length_ + 3 * side_length_ * sin_theta)));

    // fifth and last row: 3 hexes
    polygons_.push_back(QPolygonF(calculateHexPoints(0, 4 * side_length_ + 4 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(2 * side_length_ * cos_theta, 4 * side_length_ + 4 * side_length_ * sin_theta)));
    polygons_.push_back(QPolygonF(calculateHexPoints(4 * side_length_ * cos_theta, 4 * side_length_ + 4 * side_length_ * sin_theta)));

}

const QVector<QPointF> Board::calculateHexPoints(float x, float y) {
    QVector<QPointF> points;
    QPointF p1(x, y);
    QPointF p2(x + side_length_* cos_theta, y - (side_length_* sin_theta));
    QPointF p3(x + 2 *side_length_* cos_theta, y);
    QPointF p4(x + 2 * side_length_ * cos_theta, y + side_length_);
    QPointF p5(x + side_length_ * cos_theta, y + side_length_ + side_length_* sin_theta);
    QPointF p6(x, y + side_length_);

    points.append(p1);
    points.append(p2);
    points.append(p3);
    points.append(p4);
    points.append(p5);
    points.append(p6);


    for(QPointF point : points)
        std::cout << point.rx() << ", " << point.ry() << std::endl;
    return QVector<QPointF>(points);
}

