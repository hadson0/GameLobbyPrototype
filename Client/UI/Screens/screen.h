#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>
#include <QGuiApplication>

class Screen : public QFrame {
    Q_OBJECT

public:
    Screen(QWidget *parent);
    ~Screen();    

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
    int padding, spacing;

signals:
    void sendRequestMessage(QString requestMessage);
    void displayMenuScreenRequest(QString destinationScreen);
    void backRequest();
    void quitApplicationRequest();
};

#endif // SCREEN_H
