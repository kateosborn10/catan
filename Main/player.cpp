#include "player.h"
#include <iostream>
/**
 * @brief Player::Player constructor sets config field
 * @param config is struct that contains user inputed name and ai bool
 */
Player::Player(PlayerConfig* config)
{
    config_ = config;
    std::cout << "Player constructed! Name is: " << config_->name << std::endl;


}

/**
 * @brief Player::get_name
 * @return the name of the player
 */
std::string Player::get_name(){
    return config_->name;
}

/**
 * @brief Player::get_is_ai
 * @return if the player is ai controlled or not
 */
bool Player::get_is_ai(){
    return config_->is_ai;
}

/**
 * @brief Player::AddBuildingToBuildingsOwned increment players buildings_owned count
 * @param building the building type to be incremented
 */
void Player::AddBuildingToBuildingsOwned(Buildings building){
    switch(building){
    case Buildings::Wall:
        buildings_owned_->walls++;
        break;
    case Buildings::Outpost:
        buildings_owned_->outposts++;
        break;
    case Buildings::Base:
        buildings_owned_->bases++;
    }
}

/**
 * @brief Player::GetBuildingOwnedCount returns the number of a type of
 * buildings a player owns
 * @param building
 * @return number of buildings of type building
 */
int Player::GetBuildingOwnedCount(Buildings building){
    switch(building){
    case Buildings::Wall:
        return buildings_owned_->walls;
        break;
    case Buildings::Outpost:
        return buildings_owned_->outposts;
        break;
    case Buildings::Base:
        return buildings_owned_->bases;
        break;
    case Buildings::None:
        return -1;
        break;
    }
}
/**
 * @brief Player::AddResourceToHand will add a resource to the players corresponding resource
 * count in hand
 * @param resource is the resource count that needs to be incremented
 */
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

/**
 * @brief Player::RemoveResourceFromHand will decrement resource count of a given resource
 * @param resource is the resource count that needs to be decremented
 */
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
 * @brief Player::ValidateCanBuild is responsible for checking if the player
 * has enough resources to build the building
 * @param building the type of building the player wants to build
 * @return true if Player has enough resources to build the building, false otherwise
 */
bool Player::ValidateCanBuild(Buildings building){
    std::cout << "The player building is " << config_->name << std::endl;
    switch(building){
        case Buildings::Wall:{
            std::cout << "Trying to build a wall!" << std::endl;
            if(hand_->oil > 0 && hand_->steel > 0){
                std::cout << "Success! Can build a wall!" << std::endl;
                emit(ToggleBuild(false));
                return true;

            }else{
                std::cout << "Fail! Cannot build a wall!" << std::endl;
                emit(ToggleBuild(true));
                return false;
            }
            break;
        }
        case Buildings::Outpost:{
            std::cout << "Trying to build an outpost!" << std::endl;
            if(hand_->oil > 0 && hand_->steel > 0 && hand_->food > 0){
                std::cout << "Success! Can build an outpost!" << std::endl;
                emit(ToggleBuild(false));
                return true;

            }else{
                std::cout << "Fail! Cannot build an outpost!" << std::endl;
                emit(ToggleBuild(true));
                return false;
            }
            break;
        }
        case Buildings::Base:{
            std::cout << "Trying to build an base!" << std::endl;
            if(hand_->oil > 1 && hand_->steel > 1 && hand_->food > 1){
                std::cout << "Success! Can build an base!" << std::endl;
                emit(ToggleBuild(false));
                return true;
            }else{
                std::cout << "Fail! Cannot build an outpost!" << std::endl;
                emit(ToggleBuild(true));
                return false;
            }
            break;
        }
    case Buildings::None: {
            emit(ToggleBuild(true));
            return false;
        }

    }


}
