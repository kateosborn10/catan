/**
Base class for Players
Contains structs for a players hand and buildings
Keeps score
*/


#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "resource.h"
#include <vector>
#include <QObject>
#include "buildings.h"

struct PlayerConfig {
    std::string name;
    bool is_ai = false;
    int player_number;
};

struct Hand {
    int oil = 0;
    int steel = 0;
    int food = 0;
};

struct BuildingsOwned {
    int walls = 0;
    int outposts = 0;
    int bases = 0;
};

class Player: public QObject
{
    Q_OBJECT
public:
    Player(PlayerConfig* config);
    std::string get_name();
    bool get_is_ai();
    Hand* get_hand(){return hand_;}
    void set_hand(Hand* hand) {hand_ = hand;}
    BuildingsOwned* get_buildings_owned(){ return buildings_owned_;}
    void set_buildings_owned(BuildingsOwned* buildings){buildings_owned_ = buildings;}
    int GetBuildingOwnedCount(Buildings building);
    void AddBuildingToBuildingsOwned(Buildings building);
    void AddResourceToHand(Resource resource, int number);
    void RemoveResourceFromHand(Resource resource, int number);
    bool ValidateCanBuild(Buildings building);
    bool ValidateCanTrade(Resource trade_away, Resource trade_for);



public slots:


signals:
    void ToggleBuild(bool disable_value);


private:
    int score_;
    Hand* hand_ = new Hand();
    BuildingsOwned* buildings_owned_ = new BuildingsOwned();
    PlayerConfig* config_;
};

#endif // PLAYER_H
