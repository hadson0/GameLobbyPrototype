#include "navigationbutton.h"

NavigationButton::NavigationButton(QString label, QWidget *parent)
    : CustomButton(label, parent) {
    fillColor.setRgb(255, 255, 255);
    lineColor.setRgb(17, 12, 90);
    borderWidth = 3;
    borderRadius = 10;
}

void NavigationButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Reduces the rect to fit the border line
    int rRectX = this->rect().x() + borderWidth;
    int rRectY = this->rect().y() + borderWidth;
    int rRectWidth = this->rect().width() - 2 * borderWidth;
    int rRectHeight = this->rect().height() - 2 * borderWidth;
    rRect.setRect(rRectX, rRectY, rRectWidth, rRectHeight);

    // Setup the painter
    QPainter painter(this);
    QPen pen(lineColor, borderWidth);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draws a rounded rect
    QPainterPath path;
    path.addRoundedRect(rRect, borderRadius, borderRadius);
    painter.fillPath(path, fillColor);
    painter.drawPath(path);

    // Draws the text
    QFont font;
    font.setBold(true);
    font.setPixelSize(rRect.height() * 0.50);
    painter.setFont(font);
    painter.drawText(rRect, Qt::AlignCenter | Qt::TextWordWrap, label);
}

void CustomButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        emit pressed();
}

void CustomButton::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
        emit released();
}
