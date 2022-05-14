#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QFontMetrics>
#include <QPushButton>

class CustomPushButton : public QPushButton {
    Q_OBJECT

    QFont auxFont; // Auxiliar variable to manage the label text font

    void resizeEvent(QResizeEvent *event);

public:
    explicit CustomPushButton(QString text, QWidget *parent = nullptr);

    // Getters
    int getFontSize();

    // Setters
    void setFontSize(int size);
};

#endif // CUSTOMPUSHBUTTON_H
