#ifndef MOVE_H
#define MOVE_H
#include "node.h"


struct Move

{
    Node* node;
    Node* node_from; // used for a wall
    Building* building;
};
#endif // MOVE_H
