/**
Defines the playable intersections of the game board
Playable meaning intersections where outposts and bases can be placed
*/
#ifndef NODE_H
#define NODE_H
#include <QPoint>
#include <QObject>
#include <QGraphicsItem>
#include "tile.h"
#include "player.h"


class Node: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Node(QPointF position, std::vector<Tile*> tiles);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void rePaint();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void Build(Buildings building, Player* player);
//    void set_color(QColor color) { color_ = color; update(); } // inline member function
//    void set_player(Player* player){player_ = player;}
//    void set_building(Buildings building){building_ = building;}
//    void set_width(int width){width_ = width;}
    Player* get_player(){return player_;}
    Buildings get_building(){return building_;}
    std::vector<Tile*> get_tiles(){return tiles_;}
    QPointF get_position(){ return position_; }
    bool get_is_selected() { return is_selected_; }
    void set_is_selected(bool is_selected) { is_selected_ = is_selected; }
    void ClearWallFrom(){ wall_from = 0;_}


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void NodeSelected(Node* selected_node);
    void secondNodeForWallSelected(Node* firstNode, Node* secondNode);


private:
    QPointF position_;
    std::vector<Tile*> tiles_;
    Player* player_;
    Buildings building_ = Buildings::None;
    QColor color_ = "white";
    bool is_selected_ = false;
    int width_ = 8;
    int height_ = 8;
    qreal x_;
    qreal y_;
    static Node* wall_from_; // stores source Node for drawing a wall


};

#endif // NODE_H
