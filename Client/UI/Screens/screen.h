#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>
#include <QGuiApplication>

class Screen : public QFrame {
    Q_OBJECT

public:
    Screen(QWidget *parent);
    ~Screen();

    void onScreenChanged();

signals:
    void screenChanged(QString targetScreen);
};

#endif // SCREEN_H
