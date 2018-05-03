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
 * @brief Player::CalculateScore sums the number of each building type with their corresponding point value.
 * @return the total score for the player
 */
int Player::CalculateScore(){
    score_ = BuildingType_owned_->outposts + (2 * BuildingType_owned_->bases);
    return score_;
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
 * @brief Player::PoorestResource finds the resource with the lowest count.
 * Favors Oil.
 * @return the Resource type of the lowest resource count in hand_
 */
Resource Player::PoorestResource(){
    if(hand_->oil <= hand_->food){
        if(hand_->oil <= hand_->steel ){
            return Resource::Oil;
        }else{
            return Resource::Steel;
        }
    }else if(hand_->food <= hand_->steel){
        return Resource::Food;
    }else{
        return Resource::Steel;
    }


}

/**
 * @brief Player::RemoveBuildingToBuildingTypeOwned decrements the count of the
 * building type from the BuildingType owned struct.
 * @param building is the building type to be decremented
 */
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
 * @brief Player::RichestResource increments the count of the
 * building type from the BuildingType owned struct.
 * Favors Oil
 * @return
 */
Resource Player::RichestResource(){
    if(hand_->oil >= hand_->food){
        if(hand_->oil >= hand_->steel ){
            return Resource::Oil;
        }else{
            return Resource::Steel;
        }
    }else if(hand_->food >= hand_->steel){
        return Resource::Food;
    }else{
        return Resource::Steel;
    }


}

/**
 * @brief Player::ValidateCanBuild is responsible for checking if the player
 * has enough resources to build the building
 * @param building the type of building the player wants to build
 * @return true if Player has enough resources to build the building, false otherwise
 */
bool Player::ValidateCanBuild(BuildingType building){
    current_build_ = building;
    build_validated_ = false;
    switch(building){
        case BuildingType::Wall:{
            if(hand_->oil > 0 && hand_->steel > 0){
                build_validated_ = true;

            }else{
                build_validated_ = false;
            }
            break;
        }
        case BuildingType::Outpost:{
            if(hand_->oil > 0 && hand_->steel > 0 && hand_->food > 0){
                build_validated_ = true;

            }else{
                build_validated_ = false;
            }
            break;
        }
        case BuildingType::Base:{
            if(hand_->oil > 1 && hand_->steel > 1 && hand_->food > 1){
                build_validated_ = true;
            }else{
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
 * @brief Player::ValidateCanTrade checks to see if player has enough of a given resource to
 * trade it away to bank.
 * @param trade_away is resource that needs at least a count of 3 to trade away to bank
 * @param trade_for is resource that the player wants to trade for,needs not be None
 * @return true if trade is valid
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



