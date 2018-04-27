#include "playerdashboard.h"
#include <iostream>
#include <QVBoxLayout>
#include <Qstring>

/**
 * @brief PlayerDashboard::PlayerDashboard constructor. Creates all the widgets
 * that appear on the player dashboard.
 * @param parent
 */
PlayerDashboard::PlayerDashboard(QObject *parent) : QObject(parent)
{
    // build widget: contains build options combo box and build button in VBox
    QStringList buildOptions;
    buildOptions << "Select One" << "Wall" << "Outpost" << "Base";
    select_build_option_->addItems(buildOptions);
    build_layout_->addWidget(select_build_option_);
    build_layout_->addWidget(build_button_);
    build_button_->setDisabled(true);
    build_box_->setLayout(build_layout_);
    layout_->addWidget(build_box_);

    // trade widget: contains trade button and two combo boxes for trade away and trade for
    QStringList tradeForOptions;
    tradeForOptions << "Trade For" << "Oil" << "Food" << "Steel";
    QStringList tradeAwayOptions;
    tradeAwayOptions << "Trade Away" << "3 Oil" << "3 Food" << "3 Steel";
    trade_for_option_->addItems(tradeForOptions);
    trade_away_option_->addItems(tradeAwayOptions);
    trade_layout_->addWidget(trade_for_option_);
    trade_layout_->addWidget(trade_away_option_);
    trade_layout_->addWidget(trade_button_);
    trade_button_->setDisabled(true);
    trade_box_->setLayout(trade_layout_);
    layout_->addWidget(trade_box_);



    // resource widgets: images and counts. Creates ResourceWidget objects
    QPixmap oil(":/images/oil");
    QPixmap food(":/images/food");
    QPixmap steel(":/images/steel");
    oil_widget = new ResourceWidget(oil);
    food_widget = new ResourceWidget(food);
    steel_widget = new ResourceWidget(steel);
    layout_->addWidget(oil_widget->get_group_box());
    layout_->addWidget(food_widget->get_group_box());
    layout_->addWidget(steel_widget->get_group_box());
    layout_->setSpacing(10);

    // scorebox widget
    layout_->addWidget(scoreboard_box_->get_group_box());

    // set the layout of the group box to the layout with all the widgets
    group_box_->setLayout(layout_);

    // when user hits build button execute BuildButtonPressed method.
    connect(build_button_, SIGNAL(pressed()),this, SLOT(BuildButtonPressed()));

    // when user hits trade button execute TradeButtonPressed method.
    connect(trade_button_, SIGNAL(pressed()),this, SLOT(TradeButtonPressed()));

}

/**
 * @brief PlayerDashboard::UpdateCounts updates the display counts of resources and scorebox
 */
void PlayerDashboard::UpdateCounts() {
    oil_widget->UpdateCount(current_player_->get_hand()->oil);
    food_widget->UpdateCount(current_player_->get_hand()->food);
    steel_widget->UpdateCount(current_player_->get_hand()->steel);
    scoreboard_box_->UpdateCounts(current_player_->get_buildings_owned());
}

/**
 * @brief PlayerDashboard::set_current_player sets the current player field.
 * connects the signals and slots between player and dashboard.
 * @param player is the current player in the game
 */
void PlayerDashboard::set_current_player(Player *player){
    current_player_ = player;
    std::cout << "setting current player to: " << current_player_->get_name() << std::endl;
    // when user changes the index of the build options combo box call OnBuildOptionSelected method
    connect(select_build_option_, SIGNAL(currentIndexChanged(int)), this, SLOT(OnBuildOptionSelected(int)));
    // when user changes the index of the trade away options combo box call OnTradeOptionSelected method
    connect(trade_away_option_, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTradeAwayOptionSelected(int)));
    // when user changes the index of the trade away options combo box call OnTradeOptionSelected method
    connect(trade_for_option_, SIGNAL(currentIndexChanged(int)), this, SLOT(OnTradeForOptionSelected(int)));

}

/**
 * @brief PlayerDashboard::OnBuildOptionSelected slot called when user changes
 * the index of the build options combo box. Determines which building the user
 * has selected, stores this building type in current_building field, and passes it
 * to the ValidateCanBuild method on the player.
 * @param index
 */
void PlayerDashboard::OnBuildOptionSelected(int index){
    build_button_->setDisabled(true);
    current_building_ = Buildings::None;
    Buildings building;
    switch (index) {
    case 1:
        building = Buildings::Wall;
        break;
    case 2:
        building = Buildings::Outpost;
        break;
    case 3:
        building = Buildings::Base;
        break;
    default:
        std::cout << "not a valid input!" << std::endl;
        return;
    }
    if(current_player_->ValidateCanBuild(building))
        current_building_ = building;

}
/**
 * @brief PlayerDashboard::EnableBuild handles the enabling of the build button.
 * If a player has the resources to build a given building type the player class
 * emits a signal to enable the build button.
 * @param disable_value will be false if the button needs to be enable.
 */
void PlayerDashboard::EnableBuild(bool disable_value){
    build_button_->setDisabled(disable_value);
}

/**
 * @brief PlayerDashboard::ResetButtons used to reset the build and select build
 * option combo box to their initial states: disabled and "Select One" respectively
 */
void PlayerDashboard::ResetButtons(){
    build_button_->setDisabled(true);
    select_build_option_->setCurrentIndex(0);
    trade_away_option_->setCurrentIndex(0);
    trade_for_option_->setCurrentIndex(0);
    trade_button_->setDisabled(true);
}

/**
 * @brief PlayerDashboard::BuildButtonPressed for slot when user presses build this method
 * will emit a signal to the game to tell it to place the building. Will also call ResetButtons
 * method to set the intial states of the buttons.
 */
void PlayerDashboard::BuildButtonPressed() {
    std::cout << "Build Button Pressed!" << std::endl;
    emit PlaceBuilding(current_building_);
    ResetButtons();
}

/**
 * @brief PlayerDashboard::OnTradeOptionSelected
 * @param index
 */
void PlayerDashboard::OnTradeAwayOptionSelected(int index){
    trade_away_ = Resource::None;
    switch (index) {
    case 1:
        trade_away_ = Resource::Oil;
        break;
    case 2:
        trade_away_ = Resource::Food;
        break;
    case 3:
        trade_away_ = Resource::Steel;
        break;
    default:
        std::cout << "not a valid input!" << std::endl;
        break;
    }
    if(current_player_->ValidateCanTrade(trade_away_, trade_for_))
        trade_button_->setDisabled(false);
    else
        trade_button_->setDisabled(true);

}
/**
 * @brief PlayerDashboard::OnTradeOptionSelected
 * @param index
 */
void PlayerDashboard::OnTradeForOptionSelected(int index){
    trade_for_ = Resource::None;
    switch (index) {
    case 1:
        trade_for_ = Resource::Oil;
        break;
    case 2:
        trade_for_ = Resource::Food;
        break;
    case 3:
        trade_for_ = Resource::Steel;
        break;
    default:
        std::cout << "not a valid input!" << std::endl;
        break;
    }
    if(current_player_->ValidateCanTrade(trade_away_, trade_for_))
        trade_button_->setDisabled(false);
    else
        trade_button_->setDisabled(true);

}

/**
 * @brief PlayerDashboard::TradeButtonPressed
 */
void PlayerDashboard::TradeButtonPressed() {
    std::cout << "Trade Button Pressed!" << std::endl;
    current_player_->AddResourceToHand(trade_for_, 1);
    current_player_->RemoveResourceFromHand(trade_away_, 3);
    ResetButtons();
    UpdateCounts();

}
