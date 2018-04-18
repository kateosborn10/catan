/**
*
*
*/


#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "resource.h"
#include <vector>
#include <QObject>

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

struct Buildings {
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
    Buildings* get_buildings(){ return buildings_;}
    void set_buildings(Buildings* buildings){buildings_ = buildings;}
    void AddResourceToHand(Resource resource);
    void RemoveResourceFromHand(Resource resource);

public slots:
    void ValidateCanBuild(int index);

signals:
    void ToggleBuild(bool disable_value);


private:
    int score_;
    Hand* hand_ = new Hand();
    Buildings* buildings_ = new Buildings();
    PlayerConfig* config_;
};

#endif // PLAYER_H
