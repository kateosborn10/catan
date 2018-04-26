#ifndef VERTEX_H
#define VERTEX_H
#include <QPointF>


class Vertex
{
public:
    Vertex(QPointF point);
    float get_x(){return x_;}
    float get_y(){return y_;}
private:
    QPointF point_;
    float x_;
    float y_;
};

#endif // VERTEX_H
