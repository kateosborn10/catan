#include "building.h"

Building::Building(Player* owner, BuildingType type)
{
    owner_ = owner;
    type_ = type;
    color_ = owner_->get_color();
}
