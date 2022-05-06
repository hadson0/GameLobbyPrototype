#include "screen.h"

Screen::Screen(QWidget *parent)
    : QFrame{parent} {
    // A screen aways has the window's full size
    this->setGeometry(0, 0, parent->width(), parent->height());
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
