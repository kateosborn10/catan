/**
  Allows players to input their names and check a box if AI
  Creates a widget box that game can add to left side of main window
*/

#ifndef PLAYERDISPLAYHANDLER_H
#define PLAYERDISPLAYHANDLER_H

#include "player.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QtWidgets>
#include <string>
#include <QObject>

class PlayerDisplayHandler: public QObject
{
    Q_OBJECT

public:
    PlayerDisplayHandler(PlayerConfig* config, int player_number);
    QGroupBox* get_group_box() { return group_box_; }

public slots:
    void ConfigNameChanged(const QString &text);
    void ConfigIsAiChanged(bool new_value);

private:
    PlayerConfig* config_;
    std::string display_str_;
    QLineEdit* name_edit_;
    QCheckBox* is_ai_check_box_;
    QHBoxLayout *layout_ = new QHBoxLayout;
    QGroupBox* group_box_;
};

#endif // PLAYERDISPLAYHANDLER_H
