#ifndef CLIENTLISTITEM_H
#define CLIENTLISTITEM_H

#include "backgroundedframe.h"
#include "customlabel.h"

class ClientListItem : public BackgroundedFrame {
    Q_OBJECT

    CustomLabel *clientIDLabel;
    QColor defaultColor, readyColor;
    bool ready;

    void resizeEvent(QResizeEvent *event);

public:
    explicit ClientListItem(QString clientID, QWidget *parent = nullptr);

    // Getters
    bool isReady();

    // Setters
    void setReady(bool ready);

    // Methods
    void setHighlighted();
};

#endif // CLIENTLISTITEM_H
