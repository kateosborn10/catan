#include "player.h"
#include <iostream>
/**
 * @brief Player::Player constructor sets config field
 * @param config is struct that contains user inputed name and ai bool
 */
Player::Player(PlayerConfig* config)
{
    config_ = config;
    build_validated_ = false;
    current_build_ = BuildingType::None;
    is_initial_turn_ = true;
    number_of_attack_troops_ = 2;
    score_ = 0;
    attack_under_way_ = false;

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
 * @brief Player::AddBuildingToBuildingTypeOwned increment players BuildingType_owned count
 * @param building the building type to be incremented
 */
void Player::AddBuildingToBuildingTypeOwned(BuildingType building){
    switch(building){
    case BuildingType::Wall:
        BuildingType_owned_->walls++;
        break;
    case BuildingType::Outpost:
        BuildingType_owned_->outposts++;
        break;
    case BuildingType::Base:
        BuildingType_owned_->bases++;
        break;
    default:
        break;
    }
}
void Player::RemoveBuildingToBuildingTypeOwned(BuildingType building){
    switch(building){
    case BuildingType::Wall:
        BuildingType_owned_->walls--;
        break;
    case BuildingType::Outpost:
        BuildingType_owned_->outposts--;
        break;
    case BuildingType::Base:
        BuildingType_owned_->bases--;
        break;
    default:
        break;
    }
}

/**
 * @brief Player::GetBuildingOwnedCount returns the number of a type of
 * BuildingType a player owns
 * @param building
 * @return number of BuildingType of type building
 */
int Player::GetBuildingOwnedCount(BuildingType building){
    switch(building){
    case BuildingType::Wall:
        return BuildingType_owned_->walls;
        break;
    case BuildingType::Outpost:
        return BuildingType_owned_->outposts;
        break;
    case BuildingType::Base:
        return BuildingType_owned_->bases;
        break;
    case BuildingType::None:
        return -1;
        break;
    }
}
/**
 * @brief Player::AddResourceToHand will add a resource to the players corresponding resource
 * count in hand
 * @param resource is the resource count that needs to be incremented
 */
void Player::AddResourceToHand(Resource resource, int number) {
    switch(resource) {
    case Resource::Oil:
        hand_->oil += number;
        break;
    case Resource::Food:
        hand_->food += number;
        break;
    case Resource::Steel:
        hand_->steel += number;
        break;
    default:
        break;
    }
}

/**
 * @brief Player::RemoveResourceFromHand will decrement resource count of a given resource
 * @param resource is the resource count that needs to be decremented
 */
void Player::RemoveResourceFromHand(Resource resource, int number) {
    switch(resource) {
    case Resource::Oil:
        hand_->oil -= number;
        break;
    case Resource::Food:
        hand_->food -= number;
        break;
    case Resource::Steel:
        hand_->steel -= number;
        break;
    default:
        break;
    }
}

/**
 * @brief Player::ValidateCanBuild is responsible for checking if the player
 * has enough resources to build the building
 * @param building the type of building the player wants to build
 * @return true if Player has enough resources to build the building, false otherwise
 */
bool Player::ValidateCanBuild(BuildingType building){
    std::cout << "The player building is " << config_->name << std::endl; 
    current_build_ = building;
    build_validated_ = false;
    switch(building){
        case BuildingType::Wall:{
            std::cout << "Trying to build a wall!" << std::endl;
            if(hand_->oil > 0 && hand_->steel > 0){
                std::cout << "Success! Can build a wall!" << std::endl;
                build_validated_ = true;

            }else{
                std::cout << "Fail! Cannot build a wall!" << std::endl;
                build_validated_ = false;
            }
            break;
        }
        case BuildingType::Outpost:{
            std::cout << "Trying to build an outpost!" << std::endl;
            if(hand_->oil > 0 && hand_->steel > 0 && hand_->food > 0){
                std::cout << "Success! Can build an outpost!" << std::endl;
                build_validated_ = true;

            }else{
                std::cout << "Fail! Cannot build an outpost!" << std::endl;
                build_validated_ = false;
            }
            break;
        }
        case BuildingType::Base:{
            std::cout << "Trying to build an base!" << std::endl;
            if(hand_->oil > 1 && hand_->steel > 1 && hand_->food > 1){
                std::cout << "Success! Can build an base!" << std::endl;
                build_validated_ = true;
            }else{
                std::cout << "Fail! Cannot build an outpost!" << std::endl;
                build_validated_ = false;
            }
            break;
        }
    case BuildingType::None: {
            break;
        }

    }
    return build_validated_;


}

/**
 * @brief Player::ValidateCanTrade
 * @param resource
 */
bool Player::ValidateCanTrade(Resource trade_away, Resource trade_for){
    bool return_value = false;
    if(trade_away == Resource::None || trade_for == Resource::None)
        return return_value;

    switch (trade_away) {
    case Resource::Oil:
        if(hand_->oil > 2)
            return_value = true;
        break;
    case Resource::Food:
        if(hand_->food > 2)
            return_value = true;
        break;
    case Resource::Steel:
        if(hand_->steel > 2)
            return_value = true;
        break;
    default:
        break;
    }
  return return_value;
}

int Player::CalculateScore(){
    score_ = BuildingType_owned_->outposts + (2 * BuildingType_owned_->bases);
    return score_;
}
