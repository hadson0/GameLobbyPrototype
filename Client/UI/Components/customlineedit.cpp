#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent)
    : QLineEdit{parent} {}

void CustomLineEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        emit onEnterPressed();
    } else {
        QLineEdit::keyPressEvent(event);
    }
}
