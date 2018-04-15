#include "playerdashboard.h"
#include <iostream>

PlayerDashboard::PlayerDashboard(QObject *parent) : QObject(parent)
{
    oil_image_ = new QLabel();
    food_image_ = new QLabel();
    steel_image_ = new QLabel();
    QPixmap oil(":/images/oil");
    oil = oil.scaled(80, 80, Qt::KeepAspectRatio);
    QPixmap food(":/images/food");
    food = food.scaled(80, 80, Qt::KeepAspectRatio);
    QPixmap steel(":/images/steel");
    steel = steel.scaled(80, 80, Qt::KeepAspectRatio);
  //  std::cout << "Width: " << oil.width() << " height: " << oil.height() << std::endl;
    oil_image_->setPixmap(oil);
    food_image_->setPixmap(food);
    steel_image_->setPixmap(steel);

    layout_->addWidget(oil_image_);
    layout_->addWidget(food_image_);
    layout_->addWidget(steel_image_);

    group_box_ = new QGroupBox("Resources");
    group_box_->setLayout(layout_);
}
