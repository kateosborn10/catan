#include "resourcewidget.h"
#include <iostream>

/**
 * @brief ResourceWidget::ResourceWidget
 * @param map
 */
ResourceWidget::ResourceWidget(QPixmap map)
{
    map = map.scaled(80,80, Qt::KeepAspectRatio);
    image_->setPixmap(map);
    std::cout <<" map is" <<  map.width();
    layout_->addWidget(image_);
    layout_->addWidget(count_);
    group_box_->setLayout(layout_);
}

/**
 * @brief ResourceWidget::UpdateCount
 */
void ResourceWidget::UpdateCount(int count)
{
    count_->setText(QString::number(count));
}
