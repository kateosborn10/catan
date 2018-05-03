#include "node.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <math.h>


// have to forward declare the statuc fields as NULL


/**
 * @brief Node::Node
 * @param position
 * @param tiles
 */
Node::Node(QPointF position, std::vector<Tile*> tiles)
{
    position_ = position;
    x_ = position_.rx();
    y_ = position_.ry();
    tiles_ = tiles;
}

/**
 * sets the boundary rectangle of a cell to (x,y) position and width, height
 * @return  the QRectF object
 */
QRectF Node::boundingRect() const
{
    int rect_width = width_ + .75 * width_;
    int rect_height = height_ + .5 * height_;

    return QRectF(x_- .5* rect_width, y_  - .5* rect_height, rect_width, rect_height );
}

/**
 * adds the rect to the painter path
 * @return the path
 */
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(position_, width_, height_);
    return path;
}

/**
 * paint method draws the cell rectangle to the screen and fills with color
 * @param painter
 * @param option
 * @param widget
 */
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
    painter->drawEllipse(position_, width_, height_);

    painter->setBrush(b);
}

/**
 * @brief Node::mousePressEvent
 * @param event
 */
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        emit NodeSelected(this);
    if(event->button() == Qt::RightButton){
        emit WallNodeSelected(this);
    }
}

void Node::Build(BuildingType building, Player* current_player){
    switch(building){
    case BuildingType::Wall:
        players_with_incoming_walls_.push_back(current_player);
        break;
    case BuildingType::Outpost:
        std::cout << current_player->get_name() << " built and outpost!" << std::endl;
        player_ = current_player;
        color_ = player_->get_color();
        building_type_ = building;
        break;
    case BuildingType::Base:
        // if building a base at an empty node
        if(player_ == NULL){
            player_ = current_player;
            color_ = player_->get_color();
        }

        building_type_ = building;
        // need to change shape to an oval
        width_ = width_ + 2;
        height_ = height_ -2;
        break;
    default:
        break;
    }

    update();

}

float Node::CalculateDistance(Node *other){
    float diffx = x_ - other->get_position().rx();
    float diffy = y_ -other->get_position().ry();


    return sqrt((diffx * diffx) + (diffy * diffy));
}

void Node::ChangeOwner(Player* new_owner){
    player_ = new_owner;
    color_ = player_->get_color();
    update();

}

void Node::RemoveBuilding(){
    building_type_ = BuildingType::None;
    player_ = 0;
    color_ = "white";

}
