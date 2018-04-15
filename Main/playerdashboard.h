#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H

#include <QObject>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>

class PlayerDashboard : public QObject
{
    Q_OBJECT
public:
    explicit PlayerDashboard(QObject *parent = nullptr);
    QGroupBox* get_group_box() { return group_box_; }

signals:

public slots:

private:
    QLabel* oil_image_;
    QLabel* food_image_;
    QLabel* steel_image_;
    QHBoxLayout *layout_ = new QHBoxLayout;
    QGroupBox* group_box_;

};

#endif // PLAYERDASHBOARD_H
