#include "playerdashboard.h"
#include <iostream>
#include <QVBoxLayout>
#include <Qstring>

/**
 * @brief PlayerDashboard::PlayerDashboard
 * @param parent
 */
PlayerDashboard::PlayerDashboard(QObject *parent) : QObject(parent)
{
    QStringList buildOptions;
    buildOptions << "Select One" << "Wall" << "Outpost" << "Base";
    select_build_option_->addItems(buildOptions);


    QPixmap oil(":/images/oil");
    QPixmap food(":/images/food");
    QPixmap steel(":/images/steel");

    build_layout_->addWidget(select_build_option_);
    build_layout_->addWidget(build_button_);
    build_button_->setDisabled(true);
    build_box_->setLayout(build_layout_);
    layout_->addWidget(build_box_);


    oil_widget = new ResourceWidget(oil);
    food_widget = new ResourceWidget(food);
    steel_widget = new ResourceWidget(steel);
    layout_->addWidget(oil_widget->get_group_box());
    layout_->addWidget(food_widget->get_group_box());
    layout_->addWidget(steel_widget->get_group_box());
    layout_->setSpacing(10);




    group_box_->setLayout(layout_);
//    group_box_->setBackgroundRole(QPalette::ColorRole::BrightText);
}

/**
 * @brief PlayerDashboard::UpdateCounts
 */
void PlayerDashboard::UpdateCounts() {
    oil_widget->UpdateCount(current_player_->get_hand()->oil);
    food_widget->UpdateCount(current_player_->get_hand()->food);
    steel_widget->UpdateCount(current_player_->get_hand()->steel);

}

/**
 * @brief PlayerDashboard::set_current_player
 * @param player
 */
void PlayerDashboard::set_current_player(Player *player){
    current_player_ = player;
    std::cout << "setting current player to: " << current_player_->get_name() << std::endl;
    connect(select_build_option_, SIGNAL(currentIndexChanged(int)), current_player_, SLOT(ValidateCanBuild(int)));
    connect(current_player_, SIGNAL(ToggleBuild(bool)), this, SLOT(EnableBuild(bool)));
}

void PlayerDashboard::EnableBuild(bool disable_value){
    build_button_->setDisabled(disable_value);
}
