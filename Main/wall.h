#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsItem>
#include "node.h"

class Wall: public QObject
{
    Q_OBJECT
public:
    Wall(Node* from, Node* to, Player* player);
    void set_color(QColor color){ color_ = color;}
    void set_player(Player* player) { player_ = player; }
    Player* get_player(){ return player_ ; }
    QLineF get_wall() {return wall_; }
private:
    Player* player_;
    QPointF from_;
    QPointF to_;
    QColor color_;
    QLineF wall_;
};

#endif // WALL_H
