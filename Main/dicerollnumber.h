/**
  * QGraphicsEllipseItem that encapsulates the dice roll chits on Catan.
  * Draws a circle and adds dice rool number in center.
  */
#ifndef DICEROLLNUMBER_H
#define DICEROLLNUMBER_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPainter>

class DiceRollNumber : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    DiceRollNumber(QPointF center, int dice_number);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


signals:

public slots:
private:
    QPointF center_;
    qreal x_;
    qreal y_;
    int size_ = 13;
    int dice_number_;
};

#endif // DICEROLLNUMBER_H
