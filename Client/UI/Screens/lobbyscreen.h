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

    // Custom frames
    ClientListView *clientListView;
    ChatFrame *chatFrame;

    // Widgets
    CustomPushButton *backButton, *readyButton;
    CustomLabel *lobbyIDLabel;

    QString lobbyID;

    void resizeEvent(QResizeEvent *event);

public:
    explicit LobbyScreen(QString lobbyID, QWidget *parent);

public slots:
    void requestSendLobbyMessage(QString message);
    void requestToggleReady();
    void onBackButtonClicked();

signals:
    void setReady(QString clientID, bool ready);
    void newMessageRecieved(QString message);
    void clientListChanged(QStringList newClientLsit);
    void readyListChanged(QStringList newReadyList);
};

#endif // LOBBYSCREEN_H
