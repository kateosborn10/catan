#include "player.h"
#include <iostream>

Player::Player(PlayerConfig* config)
{
    hand_->oil = 0;
    hand_->steel = 0;
    hand_->food = 0;
    config_ = config;
    std::cout << "Player constructed! Name is: " << config_->name << std::endl;


}

std::string Player::get_name(){
    return config_->name;
}

bool Player::get_is_ai(){
    return config_->is_ai;
}

Hand* Player::get_hand() {
    return hand_;
}

void Player::set_hand(Hand* hand) {
    hand_ = hand;
}

void Player::AddResourceToHand(Resource resource) {
    switch(resource) {
    case Resource::Oil:
        hand_->oil++;
        break;
    case Resource::Food:
        hand_->food++;
        break;
    case Resource::Steel:
        hand_->steel++;
        break;
    }
}

void Player::RemoveResourceFromHand(Resource resource) {
    switch(resource) {
    case Resource::Oil:
        hand_->oil--;
        break;
    case Resource::Food:
        hand_->food--;
        break;
    case Resource::Steel:
        hand_->steel--;
        break;
    }
}

