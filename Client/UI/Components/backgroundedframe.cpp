#include "backgroundedframe.h"

BackgroundedFrame::BackgroundedFrame(QWidget *parent)
    : QFrame{parent}, color(75, 37, 150), borderRadius(15), padding(0), spacing(0) {
    // Disable the background (The background was visible, because it's corners are rounded)
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

QColor BackgroundedFrame::getColor() { return color; }

int BackgroundedFrame::getAvaliableWidth() {
    this->updateAvaliableSize();
    return avaliableSize.width();
}

int BackgroundedFrame::getAvaliableHeight() {
    this->updateAvaliableSize();
    return avaliableSize.height();
}

int BackgroundedFrame::getBorderRadius() { return borderRadius; }

int BackgroundedFrame::getPadding() { return padding; }

int BackgroundedFrame::getSpacing() { return spacing; }

void BackgroundedFrame::setColor(QColor color) {
    this->color = color;
    this->update();
}

void BackgroundedFrame::setBorderRadius(int borderRadius) {
    this->borderRadius = borderRadius;
    this->update();
}

void BackgroundedFrame::setPadding(int padding) {
    this->padding = padding;
    updateAvaliableSize();
}

void BackgroundedFrame::setSpacing(int spacing) {
    this->spacing = spacing;
    this->update();
}

void BackgroundedFrame::updateAvaliableSize() {
    avaliableSize.setHeight(this->height() - 2 * this->padding);
    avaliableSize.setWidth(this->width() - 2 * this->padding);
    this->update();
}

void BackgroundedFrame::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);    

    // Setup the painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(color);
    painter.setPen(pen);

    // Draws a rounded rect to be the background
    QPainterPath path;
    path.addRoundedRect(this->rect(), borderRadius, borderRadius);
    painter.fillPath(path, color);
    painter.drawPath(path);
}
