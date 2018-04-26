#include "vertex.h"


/**
 * @brief Vertex::Vertex
 * @param point
 */
Vertex::Vertex(QPointF point)
{
    point_ = point;
    x_ = point_.rx();
    y_ = point_.ry();
}
