#ifndef BACKGROUNDEDFRAME_H
#define BACKGROUNDEDFRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>

#include <QPainterPath>

class BackgroundedFrame : public QFrame {
    Q_OBJECT    

    QColor color;
    QSize avaliableSize;
    int borderRadius, padding, spacing;

public:
    explicit BackgroundedFrame(QWidget *parent = nullptr);

    // Getters
    QColor getColor();
    int getAvaliableWidth();
    int getAvaliableHeight();
    int getBorderRadius();
    int getPadding();
    int getSpacing();

    // Setters
    void setColor(QColor color);    
    void setBorderRadius(int borderRadius);
    void setPadding(int padding);
    void setSpacing(int spacing);

    // Methods
    void updateAvaliableSize();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BACKGROUNDEDFRAME_H
