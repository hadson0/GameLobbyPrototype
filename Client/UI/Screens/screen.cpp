#include "screen.h"

Screen::Screen(QWidget *parent)
    : QFrame{parent} {
    this->setGeometry(0, 0, parent->width(), parent->height());
}

Screen::~Screen(){
    this->hide();
}

int Screen::getAvaliableWidth() { return avaliableSize.width(); }

int Screen::getAvaliableHeight() { return avaliableSize.height(); }

int Screen::getPadding() {
    return padding;
}

int Screen::getSpacing() {
    return spacing;
}

void Screen::setPadding(int padding) {
    this->padding = padding;
    this->updateAvaliableSize();
}

void Screen::setSpacing(int spacing) {
    this->spacing = spacing;
}

void Screen::updateAvaliableSize() {
    avaliableSize.setHeight(this->height() - 2 * this->padding);
    avaliableSize.setWidth(this->width() - 2 * this->padding);
    this->update();
}
