#ifndef BUILDINGENUMS_H
#define BUILDINGENUMS_H

enum class BuildingType {Wall, Outpost, Base, None};

struct BuildingTypeOwned {
    int walls = 0;
    int outposts = 0;
    int bases = 0;
};

#endif // BUILDINGENUMS_H
