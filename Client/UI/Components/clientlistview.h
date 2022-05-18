#ifndef CLIENTLISTVIEW_H
#define CLIENTLISTVIEW_H

#include <QListWidget>
#include <QPushButton>

#include "backgroundedframe.h"
#include "clientlistitem.h"

class ClientListView : public BackgroundedFrame {
    Q_OBJECT

    QMap<QString, ClientListItem *> clientMap;

    void paintEvent(QPaintEvent *event);

public:
    explicit ClientListView(QWidget *parent = nullptr);

    void addClientItem(QString clientID);
    void removeClientItem(QString clientID);

public slots:
    void setReady(QString clientID, bool ready);
    void onClientListChanged(QStringList newClientList);
    void onReadyListChanged(QStringList newReadyList);
};

#endif // CLIENTLISTVIEW_H
