/**
  * Creates a group box that contains all the widgets
  * for the scoreboard.
 */
#ifndef SCOREBOARDWIDGET_H
#define SCOREBOARDWIDGET_H

#include <qwidget.h>
#include <QtWidgets>
#include <QString>
#include "player.h"

class ScoreboardWidget
{
public:
    ScoreboardWidget();
    QGroupBox* get_group_box() { return group_box_; }
    //update the widget counts with the players counts
    void UpdateCounts(BuildingsOwned* buildings);

private:
    QString WALL_LABEL_TEXT_ = "Walls: ";
    QString OUTPOST_LABEL_TEXT_ = "Outposts: ";
    QString BASE_LABEL_TEXT_ = "Bases: ";
    QString SCORE_LABEL_TEXT_ = "Score: ";

    int calculateScore(BuildingsOwned* buildings);
    QGroupBox* group_box_ = new QGroupBox();
    QLabel* wall_label_ = new QLabel("");
    QLabel* outpost_label_ = new QLabel("");
    QLabel* base_label_ = new QLabel("");
    QLabel* score_label_ = new QLabel("");
    QVBoxLayout* layout_ = new QVBoxLayout();
};

#endif // SCOREBOARDWIDGET_H
