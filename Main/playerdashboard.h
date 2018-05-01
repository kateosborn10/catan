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
#include "building.h"
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
      void PlaceBuilding(BuildingType building);
      void ToggleBuildWall(bool value);

public slots:
      void OnBuildOptionSelected(int index);
      void EnableBuild(bool disable_value);
      void BuildButtonPressed();
      void OnTradeAwayOptionSelected(int index);
      void OnTradeForOptionSelected(int index);
      void TradeButtonPressed();

private:
    BuildingType current_building_;
    Resource trade_for_ = Resource::None;
    Resource trade_away_ = Resource::None;
    QHBoxLayout* layout_ = new QHBoxLayout();
    QGroupBox* group_box_ = new QGroupBox();
    Player* current_player_;
    // build widget
    QVBoxLayout* build_layout_ = new QVBoxLayout();
    QGroupBox* build_box_ = new QGroupBox();
    QComboBox* select_build_option_ = new QComboBox();
    QPushButton* build_button_ = new QPushButton("Build");
    // trade widget
    QVBoxLayout* trade_layout_ = new QVBoxLayout();
    QGroupBox* trade_box_ = new QGroupBox();
    QComboBox* trade_for_option_ = new QComboBox();
    QComboBox* trade_away_option_ = new QComboBox();
    QPushButton* trade_button_ = new QPushButton("Trade");
    //attack widget
    QVBoxLayout* attack_layout_ = new QVBoxLayout();
    QGroupBox* attack_box_ = new QGroupBox();
    QPushButton* attack_button_ = new QPushButton("Attack");
    QLabel* attack_troops_ = new QLabel("Troops: ");
    QLineEdit* attack_count_ = new QLineEdit("0");

    // reource widgets
    ResourceWidget* oil_widget;
    ResourceWidget* food_widget;
    ResourceWidget* steel_widget;
    // scoreboard widget
    ScoreboardWidget* scoreboard_box_ = new ScoreboardWidget();
};

#endif // PLAYERDASHBOARD_H
