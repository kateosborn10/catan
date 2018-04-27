#include "dicerollnumber.h"

DiceRollNumber::DiceRollNumber(QPointF center, int dice_number){
    center_ = center;
    x_ = center_.rx();
    y_ = center_.ry();
    dice_number_ = dice_number;
}

void DiceRollNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);
    QBrush b = painter->brush();
    painter->setBrush(QBrush("white"));
    painter->drawEllipse(center_, size_, size_);
    painter->setBrush(b);
    painter->setBrush(QBrush("black"));
    painter->drawText(x_-6, y_-6, 12, 12, Qt::AlignCenter,  QString::number(dice_number_), 0);

}
