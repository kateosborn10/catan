/**
 Abstracts the playing board
 Will hold a vector of tiles, nodes, and edges
 */
#ifndef BOARD_H
#define BOARD_H
#include <QPolygon>
#include <vector>
#include <QPointF>
#include <QVector>

class Board
{
public:
    Board();
    std::vector<QPolygonF> get_polygon(){return polygons_;}


private:
    const QVector<QPointF> calculateHexPoints(float x, float y);
    std::vector<QPolygonF> polygons_;
    float cos_theta_ = 0.86602540378;
    float sin_theta_ = .5;
    int side_length_ = 55;
};

#endif // BOARD_H
