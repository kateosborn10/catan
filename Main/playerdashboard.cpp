#include "playerdashboard.h"
#include <iostream>
#include <QVBoxLayout>
#include <Qstring>
#include "resourcewidget.h"

PlayerDashboard::PlayerDashboard(QObject *parent) : QObject(parent)
{
    QStringList buildOptions;

    buildOptions << "Wall" << "Outpost" << "Base";

    select_build_option_->addItems(buildOptions);

    QPixmap oil(":/images/oil");
    QPixmap food(":/images/food");
    QPixmap steel(":/images/steel");

    build_layout_->addWidget(select_build_option_);
    build_layout_->addWidget(build_button_);
    build_box_->setLayout(build_layout_);

    layout_->addWidget(build_box_);

    ResourceWidget* oil_widget = new ResourceWidget(oil);
    ResourceWidget* food_widget = new ResourceWidget(food);
    ResourceWidget* steel_widget = new ResourceWidget(steel);
    layout_->addWidget(oil_widget->get_group_box());
    layout_->addWidget(food_widget->get_group_box());
    layout_->addWidget(steel_widget->get_group_box());



    group_box_->setLayout(layout_);
}

void PlayerDashboard::UpdateCounts() {
//    oil_count_->setText(QString::number(current_player_->get_hand()->oil));
//    food_count_->setText(QString::number(current_player_->get_hand()->food));
//    steel_count_->setText(QString::number(current_player_->get_hand()->steel));

}
