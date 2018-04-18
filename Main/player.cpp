#include "player.h"
#include <iostream>

Player::Player(PlayerConfig* config)
{
    config_ = config;
    std::cout << "Player constructed! Name is: " << config_->name << std::endl;


}

std::string Player::get_name(){
    return config_->name;
}

bool Player::get_is_ai(){
    return config_->is_ai;
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

/**
 * @brief Player::ValidateCanBuild
 * @param index is 1 then Wall, if 2 then Outpost, if 3 then Base
 */
void Player::ValidateCanBuild(int index){
    std::cout << "The player building is " << config_->name << std::endl;
    if(index == 1){
        std::cout << "Trying to build a wall!" << std::endl;
        if(hand_->oil > 0 && hand_->steel > 0){
            std::cout << "Success! Can build a wall!" << std::endl;
            emit(ToggleBuild(false));

        }else{
            std::cout << "Fail! Cannot build a wall!" << std::endl;
            emit(ToggleBuild(true));
        }
    }else if(index == 2){
        std::cout << "Trying to build an outpost!" << std::endl;
        if(hand_->oil > 0 && hand_->steel > 0 && hand_->food > 0){
            std::cout << "Success! Can build an outpost!" << std::endl;
            emit(ToggleBuild(false));

        }else{
            std::cout << "Fail! Cannot build an outpost!" << std::endl;
            emit(ToggleBuild(true));
        }
    }else if(index == 3){
        std::cout << "Trying to build an base!" << std::endl;
        if(hand_->oil > 1 && hand_->steel > 1 && hand_->food > 1){
            std::cout << "Success! Can build an base!" << std::endl;
            emit(ToggleBuild(false));

        }else{
            std::cout << "Fail! Cannot build an outpost!" << std::endl;
            emit(ToggleBuild(true));
        }
    }

}
