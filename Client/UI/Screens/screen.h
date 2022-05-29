#ifndef SCREEN_H
#define SCREEN_H

#include <QFrame>
#include <QGuiApplication>

class Screen : public QFrame {
    Q_OBJECT

    QSize avaliableSize;
    int padding, spacing;

public:
    Screen(QWidget *parent);
    ~Screen();    

    // Getters
    int getAvaliableWidth();
    int getAvaliableHeight();
    int getBorderRadius();
    int getPadding();
    int getSpacing();

    // Setters
    void setBackgroundColor(QColor color);
    void setBorderRadius(int borderRadius);
    void setPadding(int padding);
    void setSpacing(int spacing);

    // Methods
    void updateAvaliableSize();

signals:
    void menuScreenDisplayRequest(QString destinationScreen);
    void sendRequestMessage(QString requestMessage);
    void quitAppRequest();
    void backRequest();
    void error(QString errorCode);
};

#endif // SCREEN_H
