/**
Defines the playable intersections of the game board
Playable meaning intersections where outposts and bases can be placed
*/
#ifndef NODE_H
#define NODE_H
#include <QPoint>
#include "tile.h"
#include "player.h"


class Node
{
public:
    Node(QPointF position, std::vector<Tile*> tiles);
    Player* set_player(Player* player){player_ = player;}
    Buildings set_building(Buildings building){building_ = building;}
    Player* get_player(){return player_;}
    Buildings get_building(){return building_;}
    std::vector<Tile*> get_tiles(){return tiles_;}

private:
    QPointF position_;
    std::vector<Tile*> tiles_;
    Player* player_;
    Buildings building_;

};

#endif // NODE_H
