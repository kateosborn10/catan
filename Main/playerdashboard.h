#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H

#include <QObject>
#include <QWidget>

class PlayerDashboard : public QObject
{
    Q_OBJECT
public:
    explicit PlayerDashboard(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PLAYERDASHBOARD_H