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

    config_ = config;
    config_->player_number = player_number;
    name_edit_ = new QLineEdit(config_->name.c_str());
    QPalette palette;
    palette.setColor(QPalette::Base, config->color);
    palette.setColor(QPalette::Text,Qt::white);
    name_edit_->setPalette(palette);
    is_ai_check_box_ = new QCheckBox("AI");
    is_ai_check_box_->setChecked(config_->is_ai);
    is_ai_check_box_->setDisabled(true);
    group_box_ = new QGroupBox(display_str_.c_str());
    layout_->addWidget(name_edit_);
    layout_->addWidget(is_ai_check_box_);
    QObject::connect(name_edit_, SIGNAL(textChanged(QString)), this, SLOT(ConfigNameChanged(QString)));
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
