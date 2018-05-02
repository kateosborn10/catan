#ifndef BUILDING_H
#define BUILDING_H
#include <QObject>
#include <QLineF>
#include "buildingenums.h"
#include "player.h"



class Building: public QObject
{
    Q_OBJECT
public:
    Building(BuildingType type);
    BuildingType get_building_type(){ return type_; }
    virtual QLineF get_wall(){ return QLineF(); }

private:
    BuildingType type_;
    QColor color_;
};

#endif // BUILDING_H
