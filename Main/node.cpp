#include "node.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <math.h>

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
 * @brief Node::Build is called by Game to encapsulate a building on the node.
 * This is achieved by setting player and building type to the param values and
 * coloring the node the color of the player to display ownership. If the building type
 * is a base then the shape is altered to be an oval.
 * @param building is the type of the building to be displayed on the node
 * @param current_player is the owner of the building
 */
void Node::Build(BuildingType building, Player* current_player){
    switch(building){
    case BuildingType::Wall:
        players_with_incoming_walls_.push_back(current_player);
        break;
    case BuildingType::Outpost:
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
 * @brief Node::CalculateDistance finds the euclidian distance between two node objects.
 * Used by game to verify a wall is allowed. A disance between 0-55 represents a valid wall.
 * @param other is the node to calculate distance to.
 * @return the distance as float
 */
float Node::CalculateDistance(Node *other){
    float diffx = x_ - other->get_position().rx();
    float diffy = y_ -other->get_position().ry();


    return sqrt((diffx * diffx) + (diffy * diffy));
}


/**
 * @brief Node::mousePressEvent emits a signal to game when the user clicks on a node.
 * If user right clicks then this slot tells game to build a wall, if user left clicks
 * then slot tells game to build a non-wall building.
 * @param event
 */
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        emit NodeSelected(this);
    if(event->button() == Qt::RightButton){
        emit WallNodeSelected(this);
    }
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
    Q_UNUSED(option);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
    painter->drawEllipse(position_, width_, height_);

    painter->setBrush(b);
}

void Node::RemoveBuilding(){
    building_type_ = BuildingType::None;
    player_ = 0;
    color_ = "white";

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


