#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H

#include <QFrame>

#include "screen.h"
#include "Controllers/gamemanager.h"
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

    GameManager *gameManager;

    void resizeEvent(QResizeEvent *event);

public:
    explicit LobbyScreen(QString lobbyID, GameManager *gameManager, QWidget *parent);
};

#endif // LOBBYSCREEN_H
