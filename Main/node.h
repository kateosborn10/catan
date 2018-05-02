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
    void Build(BuildingType building, Player* current_player);
    Player* get_player(){return player_;}
    BuildingType get_building_type(){ return building_type_; }
    std::vector<Tile*> get_tiles(){return tiles_;}
    QPointF get_position(){ return position_; }
    bool get_is_selected() { return is_selected_; }
    void set_is_selected(bool is_selected) { is_selected_ = is_selected; }
    std::vector<Player*> get_players_with_incoming_walls(){ return players_with_incoming_walls_; }
    float CalculateDistance(Node* other);
    void ChangeOwner(Player* new_owner);
    void RemoveBuilding();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void NodeSelected(Node* selected_node);
    void WallNodeSelected(Node* selected_node);


private:
    QPointF position_;
    std::vector<Tile*> tiles_;
    Player* player_ = 0;
    BuildingType building_type_ = BuildingType::None;
    QColor color_ = "white";
    bool is_selected_ = false;
    int width_ = 8;
    int height_ = 8;
    qreal x_;
    qreal y_;
//    static Node* wall_from_; // stores source Node for drawing a wall
    std::vector<Player*> players_with_incoming_walls_;


};

#endif // NODE_H
