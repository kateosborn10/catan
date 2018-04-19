#include "resourcewidget.h"
#include <iostream>

/**
 * @brief ResourceWidget::ResourceWidget creates a group box that
 * represents a resource. Has an image and a label displaying count
 * @param map is the Qpixmap of the resource image
 */
ResourceWidget::ResourceWidget(QPixmap map)
{
    map = map.scaled(80,80, Qt::KeepAspectRatio);
    image_->setPixmap(map);
    layout_->addWidget(image_);
    layout_->addWidget(count_);
    group_box_->setLayout(layout_);
}

/**
 * @brief ResourceWidget::UpdateCount sets the label displaying
 * the count to the param count.
 * @param count is the current resource count corresponding to the player
 */
void ResourceWidget::UpdateCount(int count)
{
    count_->setText(QString::number(count));
}
