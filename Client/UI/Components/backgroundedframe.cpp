#include "backgroundedframe.h"

BackgroundedFrame::BackgroundedFrame(QWidget *parent)
    : QFrame{parent}, backgroundColor(75, 37, 150), borderRadius(15) {
    // Disable the background (The background was visible, because it's corners are rounded)
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void BackgroundedFrame::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Setup the painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(backgroundColor);
    painter.setPen(pen);

    // Draws a rounded rect
    QPainterPath path;
    path.addRoundedRect(this->rect(), borderRadius, borderRadius);
    painter.fillPath(path, backgroundColor);
    painter.drawPath(path);
}
