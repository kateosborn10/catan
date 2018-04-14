#include "aiplayer.h"
#include <iostream>


AiPlayer::AiPlayer(PlayerConfig* config):
    Player(config)
{
    std::cout << "AIPlayer constructed!" << std::endl;

}
