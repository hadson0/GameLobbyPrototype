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
    explicit ClientListItem(QString uniqueID, bool highlighted, QWidget *parent = nullptr);

    void toggleReady();
    void setHighlighted();

signals:

};

#endif // CLIENTLISTITEM_H
