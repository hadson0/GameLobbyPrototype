#include "custompushbutton.h"

CustomPushButton::CustomPushButton(QString text, QWidget *parent)
    : QPushButton{text, parent} {
    // Sets the style
    this->setStyleSheet("QPushButton {"
                            "background-color: white; "
                            "border-radius: 15px; "
                            "border: 0px;"
                            "font-weight: bold;"
                            "color: #110C5A;"
                        "}"

                        "QPushButton:pressed {background-color: #CABFE0;}");
}

void CustomPushButton::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    setFontSize((this->height()) * 0.40);
}

void CustomPushButton::setFontSize(int size) {
    auxFont = this->font();
    auxFont.setPixelSize(size);
    this->setFont(auxFont);
    auxFont.setPixelSize(size);
}

int CustomPushButton::getFontSize() {
    auxFont = this->font();
    return auxFont.pixelSize();
}
