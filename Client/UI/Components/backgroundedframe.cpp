#include "backgroundedframe.h"

BackgroundedFrame::BackgroundedFrame(QWidget *parent)
    : QFrame{parent}, backgroundColor(75, 37, 150), borderRadius(15), padding(0), spacing(0) {
    // Disable the background (The background was visible, because it's corners are rounded)
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

QColor BackgroundedFrame::getBackgroundColor() {
    return backgroundColor;
}

int BackgroundedFrame::getBorderRadius() {
    return borderRadius;
}

int BackgroundedFrame::getPadding() {
    return padding;
}

int BackgroundedFrame::getSpacing() {
    return spacing;
}

void BackgroundedFrame::setBackgroundColor(QColor color) {
    backgroundColor = color;
}

void BackgroundedFrame::setBorderRadius(int borderRadius) {
    this->borderRadius = borderRadius;
}

void BackgroundedFrame::setPadding(int padding) {
    this->padding = padding;
}

void BackgroundedFrame::setSpacing(int spacing) {
    this->spacing = spacing;
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
