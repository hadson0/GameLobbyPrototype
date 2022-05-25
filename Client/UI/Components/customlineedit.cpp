#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent)
    : QLineEdit{parent} {
    // Sets the style
    this->setStyleSheet("QLineEdit {"
                            "background-color: #E3DDF0; border-radius: 15px;"
                            "padding: 5px;"
                            "color: #110C5A;"
                        "}" );
}

void CustomLineEdit::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    setFontSize(this->height() * 0.75);
}

int CustomLineEdit::getFontSize() {
    auxFont = this->font();
    return auxFont.pixelSize();
}

void CustomLineEdit::setFontSize(int size) {
    auxFont = this->font();
    auxFont.setPixelSize(size);
    this->setFont(auxFont);
    auxFont.setPixelSize(size);
}


