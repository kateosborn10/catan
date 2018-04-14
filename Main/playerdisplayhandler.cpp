#include "playerdisplayhandler.h"
#include <iostream>
#include <string>

/**
 * @brief PlayerDisplayHandler::PlayerDisplayHandler
 * @param config is the player configuration that will be updated
 * @param player_number is the number of the player that is used in player display
 */
PlayerDisplayHandler::PlayerDisplayHandler(PlayerConfig* config, int player_number)
{
    display_str_ = "Player " + std::to_string(player_number);
    config_ = config;
    config_->player_number = player_number;
    //set the default name of the player to config string if its empty, otherwise
    //use the already set config value
    if(config_->name.empty())
        config_->name = display_str_;
    name_edit_ = new QLineEdit(config_->name.c_str());
    is_ai_check_box_ = new QCheckBox("AI");
    is_ai_check_box_->setChecked(config_->is_ai);
    group_box_ = new QGroupBox(display_str_.c_str());
    layout_->addWidget(name_edit_);
    layout_->addWidget(is_ai_check_box_);
    QObject::connect(name_edit_, SIGNAL(textChanged(QString)), this, SLOT(ConfigNameChanged(QString)));
    QObject::connect(is_ai_check_box_, SIGNAL(clicked(bool)), this, SLOT(ConfigIsAiChanged(bool)));
    layout_->addStretch(1);
    group_box_->setLayout(layout_);

}

/**
 * @brief PlayerDisplayHandler::ConfigNameChanged
 * @param text is the input string from the user
 */
void PlayerDisplayHandler::ConfigNameChanged(const QString &text) {
    config_->name = text.toStdString();
}

/**
 * @brief PlayerDisplayHandler::ConfigIsAiChanged
 * @param new_value is true if user checked AI box or false if unchecked
 */
void PlayerDisplayHandler::ConfigIsAiChanged(bool new_value) {
    config_->is_ai = new_value;
}
