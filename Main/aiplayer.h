/**
 Inherits Player Object
 Abstracts the AI controlled players
*/
#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "player.h"




class AiPlayer: public Player
{
public:
    AiPlayer(PlayerConfig* config);

};

#endif // AIPLAYER_H
