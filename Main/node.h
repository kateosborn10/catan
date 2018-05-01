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
#include "building.h"



class Node: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Node(QPointF position, std::vector<Tile*> tiles);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void rePaint();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    void Build(Building* building);
    Player* get_player(){return player_;}
    BuildingType get_building(){return building_;}
    std::vector<Tile*> get_tiles(){return tiles_;}
    QPointF get_position(){ return position_; }
    bool get_is_selected() { return is_selected_; }
    void set_is_selected(bool is_selected) { is_selected_ = is_selected; }
    void ClearWallFrom(){ wall_from_ = 0; }
    std::vector<Building*> get_incoming_walls(){ return incoming_walls_; }
    float CalculateDistance(Node* other);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void NodeSelected(Node* selected_node);
    void secondNodeForWallSelected(Node* firstNode, Node* secondNode);


private:
    QPointF position_;
    std::vector<Tile*> tiles_;
    Player* player_ = 0;
    BuildingType building_ = BuildingType::None;
    QColor color_ = "white";
    bool is_selected_ = false;
    int width_ = 8;
    int height_ = 8;
    qreal x_;
    qreal y_;
    static Node* wall_from_; // stores source Node for drawing a wall
    std::vector<Building*> incoming_walls_;


};

#endif // NODE_H
