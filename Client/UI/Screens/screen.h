#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>
#include <QGuiApplication>

class Screen : public QFrame {
    Q_OBJECT

public:
    Screen(QWidget *parent);
    ~Screen();

signals:
    void sendRequestMessage(QString requestMessage);
    void displayMenuScreenRequest(QString destinationScreen);
    void backRequest();
    void quitApplicationRequest();
};

#endif // SCREEN_H
