#ifndef CLIENTLISTVIEW_H
#define CLIENTLISTVIEW_H

#include <QListWidget>
#include <QDebug>
#include <QPushButton>

#include "backgroundedframe.h"
#include "clientlistitem.h"

class ClientListView : public BackgroundedFrame {
    Q_OBJECT


    QMap<QString, ClientListItem *> clientMap;

    void paintEvent(QPaintEvent *event);

public:
    explicit ClientListView(QWidget *parent = nullptr);

    void addClientItem(QString clientID, bool highlighted = false);

public slots:
    void toggleReady(QString clientID);
    void onClientListChanged(QStringList clientList);

signals:

};

#endif // CLIENTLISTVIEW_H
