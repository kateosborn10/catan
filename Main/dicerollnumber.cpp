#include "dicerollnumber.h"

/**
 * @brief DiceRollNumber::DiceRollNumber constructor sets x_ and y_ fields to the center of the Hex
 * @param center is the center point of the hexagon
 * @param dice_number is the number to be displayed on the hex
 */
DiceRollNumber::DiceRollNumber(QPointF center, int dice_number){
    center_ = center;
    x_ = center_.rx();
    y_ = center_.ry();
    dice_number_ = dice_number;
}

/**
 * @brief DiceRollNumber::paint method draws an ellipse, colors it white and adds dice number to center
 * @param painter Qt object used to set brush and draw the text in the ellipse
 * @param item Qt object which is unused
 * @param widget Qt object which is unused.
 */
void DiceRollNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);
    Q_UNUSED(item);
    QBrush b = painter->brush();
    painter->setBrush(QBrush("white"));
    painter->drawEllipse(center_, size_, size_);
    painter->setBrush(b);
    painter->setBrush(QBrush("black"));
    painter->drawText(x_-6, y_-6, 12, 12, Qt::AlignCenter,  QString::number(dice_number_), 0);

}
