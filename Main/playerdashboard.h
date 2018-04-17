#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H

#include <QObject>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <player.h>

class PlayerDashboard : public QObject
{
    Q_OBJECT
public:
    explicit PlayerDashboard(QObject *parent = nullptr);
    QGroupBox* get_group_box() { return group_box_; }
    void set_current_player(Player* player) { current_player_ = player; }
    Player* get_current_player() { return current_player_; }
    void UpdateCounts();

signals:

public slots:

private:
    QHBoxLayout* layout_ = new QHBoxLayout();
    QGroupBox* group_box_ = new QGroupBox();
    Player* current_player_;
    QVBoxLayout* build_layout_ = new QVBoxLayout();
    QGroupBox* build_box_ = new QGroupBox();
    QComboBox* select_build_option_ = new QComboBox();
    QPushButton* build_button_ = new QPushButton("Build");
};

#endif // PLAYERDASHBOARD_H
