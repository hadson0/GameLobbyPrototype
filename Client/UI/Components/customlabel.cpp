#include "customlabel.h"

CustomLabel::CustomLabel(QString text, QWidget *parent)
    : QLabel{text, parent} {
    // Set alignment center
    this->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    // Sets the style
    this->setStyleSheet("QLabel { "
                            "color: white;"
                            "font-weight: bold;"
                        "}");
}

void CustomLabel::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    setFontSize(this->height() * 0.85);
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
