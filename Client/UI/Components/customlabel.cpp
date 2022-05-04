#include "customlabel.h"

CustomLabel::CustomLabel(QString text, QWidget *parent)
    : QLabel{text, parent} {
    // Set alignment center
    this->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
}

void CustomLabel::setFontSize(int size) {
    fontAux = this->font();
    fontAux.setPixelSize(size);
    this->setFont(fontAux);
    fontAux.setPixelSize(size);
}
