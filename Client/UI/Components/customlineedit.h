#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class CustomLineEdit : public QLineEdit {
    Q_OBJECT

    QFont auxFont; // Auxiliar variable to manage the label text font

    void resizeEvent(QResizeEvent *event);

public:
    explicit CustomLineEdit(QWidget *parent = nullptr);

    // Getters
    int getFontSize();

    // Setters
    void setFontSize(int size);
};

#endif // CUSTOMLINEEDIT_H
