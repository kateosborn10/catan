#ifndef BUILDING_H
#define BUILDING_H
#include <QObject>
#include <QLineF>
#include "player.h"
#include "buildingenums.h"



class Building: public QObject
{
    Q_OBJECT
public:
    Building(BuildingType type);
    BuildingType get_building_type(){ return type_; }
//    Player* get_player(){ return owner_ ;}
//    void ChangeOwner(Player* new_player){ owner_ = new_player; }
    virtual QLineF get_wall(){ return QLineF(); }

private:
    BuildingType type_;
    Player* owner_;
    QColor color_;
};

#endif // BUILDING_H
