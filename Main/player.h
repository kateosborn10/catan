/**
Base class for Players
Contains structs for a players hand and BuildingType
Keeps score
*/


#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "resource.h"
#include <vector>
#include <QObject>
#include "buildingenums.h"
#include <QColor>


struct PlayerConfig {
    std::string name;
    bool is_ai = false;
    int player_number;
    QColor color;
};

struct Hand {
    int oil = 4;
    int steel = 4;
    int food = 2;
};



class Player: public QObject
{
    Q_OBJECT
public:
    Player(PlayerConfig* config);
    std::string get_name();
    bool get_build_validate(){ return build_validated_; }
    void set_build_validate(bool value){ build_validated_ =  value; }
    bool get_is_ai();
    bool get_is_initial_turn(){ return is_initial_turn_; }
    void set_is_initial_turn(bool value){ is_initial_turn_ = value; }
    int CalculateScore();
    int get_number_attack_troops(){ return number_of_attack_troops_; }
    void IncrementTroopCount(int number){ number_of_attack_troops_ += number; }
    void DecrementTroopCount(int number){ number_of_attack_troops_ -= number; }
    BuildingType get_current_build(){ return current_build_; }
    Hand* get_hand(){return hand_;}
    void set_hand(Hand* hand) {hand_ = hand;}
    BuildingTypeOwned* get_BuildingType_owned(){ return BuildingType_owned_;}
//    void set_BuildingType_owned(BuildingTypeOwned* BuildingType){BuildingType_owned_ = BuildingType;}
    int GetBuildingOwnedCount(BuildingType building);
    void AddBuildingToBuildingTypeOwned(BuildingType building);
    void RemoveBuildingToBuildingTypeOwned(BuildingType building);
    void AddResourceToHand(Resource resource, int number);
    void RemoveResourceFromHand(Resource resource, int number);
    bool ValidateCanBuild(BuildingType building);
    bool ValidateCanTrade(Resource trade_away, Resource trade_for);
    QColor get_color() { return config_->color; }
    void set_color(QColor color) { config_->color = color;}
    void set_attack_under_way(bool value) { attack_under_way_ = value; }
    bool get_attack_under_way() { return attack_under_way_; }
//    virtual void MakeMove(std::vector<Move> possible_moves);

public slots:


signals:


private:
    int score_;
    int number_of_attack_troops_;
    Hand* hand_ = new Hand();
    BuildingTypeOwned* BuildingType_owned_ = new BuildingTypeOwned();
    PlayerConfig* config_;
    bool build_validated_;
    BuildingType current_build_;
    bool is_initial_turn_;
    bool attack_under_way_;

};

#endif // PLAYER_H
