/**
  Creates a widget box with resource information
  Is used by PlayerDashboard class
 */
#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <qwidget.h>
#include <QtWidgets>
#include <QString>
#include "resource.h"

class ResourceWidget
{
public:
    ResourceWidget(QPixmap map, Resource resource);
    QGroupBox* get_group_box(){return group_box_;}
    void UpdateCount(int count);
private:
    QLabel* image_ = new QLabel;
    QLabel* count_ = new QLabel("0");
    QVBoxLayout* layout_ = new QVBoxLayout();
    QGroupBox* group_box_ = new QGroupBox();
};

#endif // RESOURCEWIDGET_H
