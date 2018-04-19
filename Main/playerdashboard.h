#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H
/**
  Player dashboard shows at bottom of main window
  Displays resources and their respective count on each player's turn
  Gives build options
*/
#include <QObject>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <player.h>
#include "resourcewidget.h"
#include "buildings.h"
#include "scoreboardwidget.h"

class PlayerDashboard : public QObject
{
    Q_OBJECT
public:
    explicit PlayerDashboard(QObject *parent = nullptr);
    QGroupBox* get_group_box() { return group_box_; }
    void set_current_player(Player* player);
    Player* get_current_player() { return current_player_; }
    void UpdateCounts();
    void ResetButtons(); // reset buttons on dashboard to initial sates

signals:
      void PlaceBuilding(Buildings building);

public slots:
      void OnBuildOptionSelected(int index);
      void EnableBuild(bool disable_value);
      void BuildButtonPressed();

private:
    QHBoxLayout* layout_ = new QHBoxLayout();
    QGroupBox* group_box_ = new QGroupBox();
    Player* current_player_;
    QVBoxLayout* build_layout_ = new QVBoxLayout();
    QGroupBox* build_box_ = new QGroupBox();
    QComboBox* select_build_option_ = new QComboBox();
    QPushButton* build_button_ = new QPushButton("Build");
    ResourceWidget* oil_widget;
    ResourceWidget* food_widget;
    ResourceWidget* steel_widget;
    Buildings current_building_;
    ScoreboardWidget* scoreboard_box_ = new ScoreboardWidget();
};

#endif // PLAYERDASHBOARD_H
