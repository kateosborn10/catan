/**
*
*
*/


#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "resource.h"
#include <vector>

struct PlayerConfig {
    std::string name;
    bool is_ai = false;
    int player_number;
};

struct Hand {
    int oil;
    int steel;
    int food;
};

class Player
{
public:
    Player(PlayerConfig* config);
    std::string get_name();
    bool get_is_ai();
    Hand* get_hand();
    void set_hand(Hand* hand);
    void AddResourceToHand(Resource resource);
    void RemoveResourceFromHand(Resource resource);

private:
    std::string name_;
    int score_;
    Hand* hand_ = new Hand();
    PlayerConfig* config_;
};

#endif // PLAYER_H
