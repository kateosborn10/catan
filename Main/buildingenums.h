/**
  * Holds BuildingType enum class and BuildingTypeOwned struct.
  * BuildingType is used in lieu of Building objects in most cases.
  * BuildingTypeOwned is used by player to keep track of what buildings they have, and to keep score.
  */
#ifndef BUILDINGENUMS_H
#define BUILDINGENUMS_H

enum class BuildingType {Wall, Outpost, Base, None};

struct BuildingTypeOwned {
    int walls = 0;
    int outposts = 0;
    int bases = 0;
};

#endif // BUILDINGENUMS_H
