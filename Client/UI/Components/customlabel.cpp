#include "customlabel.h"

CustomLabel::CustomLabel(QString text, QWidget *parent)
    : QLabel{text, parent} {
    // Set alignment center
    this->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
}

void CustomLabel::setFontSize(int size) {
    auxFont = this->font();
    auxFont.setPixelSize(size);
    this->setFont(auxFont);
    auxFont.setPixelSize(size);
}

int CustomLabel::getFontSize() {
    auxFont = this->font();
    return auxFont.pixelSize();
}
