#include "screen.h"

Screen::Screen(QWidget *parent)
    : QFrame{parent} {
    // A screen aways has the window's full size
    this->setFixedSize(parent->width(), parent->height());
    move(0, 0);
}

Screen::~Screen(){
    this->hide();
}

int Screen::getPadding() {
    return padding;
}

int Screen::getSpacing() {
    return spacing;
}

void Screen::setPadding(int padding) {
    this->padding = padding;
}

void Screen::setSpacing(int spacing) {
    this->spacing = spacing;
}
