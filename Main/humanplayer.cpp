#include "humanplayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(PlayerConfig* config):
    Player(config)
{
    std::cout << "Human Player constructed!" << std::endl;

}
