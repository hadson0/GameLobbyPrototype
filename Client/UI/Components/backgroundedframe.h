#ifndef BACKGROUNDEDFRAME_H
#define BACKGROUNDEDFRAME_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>

#include <QPainterPath>

class BackgroundedFrame : public QFrame {
    Q_OBJECT    

public:
    explicit BackgroundedFrame(QWidget *parent = nullptr);

protected:
    QColor backgroundColor;
    int borderRadius;

    void paintEvent(QPaintEvent *event);

signals:

};

#endif // BACKGROUNDEDFRAME_H
