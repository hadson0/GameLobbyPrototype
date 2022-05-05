#include "screen.h"

Screen::Screen(QWidget *parent)
    : QFrame{parent} {
    // A screen aways has the window's full size
    this->setGeometry(0, 0, parent->width(), parent->height());
}

Screen::~Screen(){
    this->hide();
}
