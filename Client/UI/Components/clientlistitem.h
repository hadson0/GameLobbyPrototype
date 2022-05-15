#ifndef CLIENTLISTITEM_H
#define CLIENTLISTITEM_H

#include "backgroundedframe.h"
#include "customlabel.h"

class ClientListItem : public BackgroundedFrame {
    Q_OBJECT

    CustomLabel *clientIDLabel;
    QColor defaultColor, readyColor;
    bool isReady;

    void resizeEvent(QResizeEvent *event);

public:
    explicit ClientListItem(QString clientID, bool isHighlighted, QWidget *parent = nullptr);

    void toggleReady();
    void setHighlighted();
};

#endif // CLIENTLISTITEM_H
