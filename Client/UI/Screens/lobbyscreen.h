#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H

#include <QFrame>

#include "screen.h"
#include "UI/Components/clientlistview.h"
#include "UI/Components/chatframe.h"
#include "UI/Components/customlabel.h"

class LobbyScreen : public Screen {
    Q_OBJECT

    int padding;

    CustomLabel *lobbyIDLabel;
    ClientListView *clientListView;
    ChatFrame *chatFrame;
    QString lobbyID;

    void resizeEvent(QResizeEvent *event);

public:
    explicit LobbyScreen(QString lobbyID, QWidget *parent);

public slots:
    void requestSendLobbyMessage(QString message);

signals:
    void newMessageRecieved(QString message);
};

#endif // LOBBYSCREEN_H
