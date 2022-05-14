#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H

#include <QFrame>

#include "screen.h"
#include "UI/Components/clientlistview.h"
#include "UI/Components/chatframe.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/custompushbutton.h"

class LobbyScreen : public Screen {
    Q_OBJECT

    CustomPushButton *backButton, *readyButton;
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
    void clientListChanged(QStringList clientLsit);
};

#endif // LOBBYSCREEN_H
