#ifndef CLIENTLISTVIEW_H
#define CLIENTLISTVIEW_H

#include <QFrame>
#include <QListWidget>

#include "backgroundedframe.h"

class ClientListView : public BackgroundedFrame {
    Q_OBJECT

    QListWidget *clientWidgetList;

    //void resizeEvent(QResizeEvent *event);

public:
    explicit ClientListView(QWidget *parent = nullptr);

public slots:
    //void onClientJoined(QStringList );


signals:

};

#endif // CLIENTLISTVIEW_H
