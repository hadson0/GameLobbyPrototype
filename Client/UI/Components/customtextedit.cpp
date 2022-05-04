#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget *parent)
    : QTextEdit{parent} {
    this->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    fontAux = this->font();
    fontAux.setPixelSize(20);
}

void CustomTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        emit onEnterPressed();
    } else {
        QTextEdit::keyPressEvent(event);
    }
}
