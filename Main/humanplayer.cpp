#include "humanplayer.h"
#include <iostream>

/**
 * @brief HumanPlayer::HumanPlayer
 * @param config
 */
HumanPlayer::HumanPlayer(PlayerConfig* config):
    Player(config)
{
    std::cout << "Human Player constructed!" << std::endl;

}
