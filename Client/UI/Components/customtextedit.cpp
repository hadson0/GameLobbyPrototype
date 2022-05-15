#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget *parent)
    : QTextEdit{parent} {
    this->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    fontAux = this->font();
    fontAux.setPixelSize(20);

    // Sets the style
    this->setStyleSheet("QTextEdit {"
                            "background-color: #E3DDF0; border-radius: 15px;"
                            "padding: 5px;"
                            "color: #110C5A;"
                        "}");
}

void CustomTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter) {
        emit enterPressed();
    } else {
        QTextEdit::keyPressEvent(event);
    }
}
