#include "screen.h"

Screen::Screen(QWidget *parent)
    : QFrame{parent} {
    // A screen aways has the window's full size
    this->setFixedSize(parent->width(), parent->height());
    this->move(0, 0);
}

Screen::~Screen(){
    onScreenChanged();
}

void Screen::onScreenChanged() {
    this->hide();
}
