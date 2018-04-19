/**
  Inherits the Player object
  Abstracts the human controlled player
*/

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"


class HumanPlayer: public Player
{
public:
    HumanPlayer(PlayerConfig* config);
};

#endif // HUMANPLAYER_H
