#ifndef BACKGROUNDEDFRAME_H
#define BACKGROUNDEDFRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>

#include <QPainterPath>

class BackgroundedFrame : public QFrame {
    Q_OBJECT    

    QColor backgroundColor;
    int borderRadius, padding, spacing;

public:
    explicit BackgroundedFrame(QWidget *parent = nullptr);

    // Getters
    QColor getBackgroundColor();
    int getBorderRadius();
    int getPadding();
    int getSpacing();

    // Setters
    void setBackgroundColor(QColor color);
    void setBorderRadius(int borderRadius);
    void setPadding(int padding);
    void setSpacing(int spacing);

protected:
    void paintEvent(QPaintEvent *event);

signals:

};

#endif // BACKGROUNDEDFRAME_H
