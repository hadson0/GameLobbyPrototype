#ifndef NAVIGATIONBUTTON_H
#define NAVIGATIONBUTTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

#include "custombutton.h"

class NavigationButton : public CustomButton {
    Q_OBJECT

    QRect rRect;
    QColor fillColor, lineColor;
    int borderWidth;
    int borderRadius;

    void paintEvent(QPaintEvent *event);

public:
    NavigationButton(QString label, QWidget *parent);
};

#endif // NAVIGATIONBUTTON_H
