#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <qwidget.h>
#include <QtWidgets>
#include <QString>

class ResourceWidget
{
public:
    ResourceWidget(QPixmap map);
    QGroupBox* get_group_box(){return group_box_;}
    void UpdateCount(int count);
private:
    QLabel* image_ = new QLabel;
    QLabel* count_ = new QLabel("0");
    QVBoxLayout* layout_ = new QVBoxLayout();
    QGroupBox* group_box_ = new QGroupBox();


};

#endif // RESOURCEWIDGET_H
