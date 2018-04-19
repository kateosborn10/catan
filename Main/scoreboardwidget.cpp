#include "scoreboardwidget.h"
#include <iostream>

/**
 * @brief ScoreboardWidget::ScoreboardWidget adds all the label
 * widgets for building tallies to the scoreboard layout.
 */
ScoreboardWidget::ScoreboardWidget()
{
    // allows for concatenation to avoid two different labels
    WALL_LABEL_TEXT_ = "Walls: ";
    OUTPOST_LABEL_TEXT_ = "Outposts: ";
    BASE_LABEL_TEXT_ = "Bases: ";
    SCORE_LABEL_TEXT_ = "Score: ";

    layout_->addWidget(wall_label_);
    layout_->addWidget(outpost_label_);
    layout_->addWidget(base_label_);
    layout_->addWidget(score_label_);
    group_box_->setLayout(layout_);
}
/**
 * @brief ScoreboardWidget::UpdateCounts displays the current building counts
 * @param buildings is a struct that contains the number of walls, outpost, and
 * bases that a player owns.
 */
void ScoreboardWidget::UpdateCounts(BuildingsOwned* buildings) {
    std::cout << "Updating score" << std::endl;
    wall_label_->setText(WALL_LABEL_TEXT_ + QString::number(buildings->walls));
    outpost_label_->setText(OUTPOST_LABEL_TEXT_ + QString::number(buildings->outposts));
    base_label_->setText(BASE_LABEL_TEXT_ + QString::number(buildings->bases));
    score_label_->setText(SCORE_LABEL_TEXT_ + QString::number(calculateScore(buildings)));
}

/**
 * @brief ScoreboardWidget::calculateScore uses the counts contained in buildings
 * to calculate the score of the player
 * @param buildings is a struct that contains the number of walls, outposts, and bases
 * that a player owns
 * @return the current score of the player
 */
int ScoreboardWidget::calculateScore(BuildingsOwned* buildings) {
    int score = 0;
    score += buildings->outposts;
    score += (buildings->bases * 2);
    return score;
}
