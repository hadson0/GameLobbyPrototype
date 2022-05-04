#ifndef JOINLOBBYSCREEN_H
#define JOINLOBBYSCREEN_H

#include <QPushButton>
#include <QIntValidator>

#include "screen.h"
#include "Controllers/gamemanager.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/customlineedit.h"

class JoinLobbyScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    QPushButton *joinButton, *backButton;
    CustomLineEdit *lobbyIDInputEdit;

    GameManager *gameManager;

    void resizeEvent(QResizeEvent *event);

public:
    explicit JoinLobbyScreen(GameManager *gameManager, QWidget *parent = nullptr);

public slots:
    void onBackButtonClicked();
    void onJoinButtonClicked();

    void onLobbyIDChanged(QString newLobbyID);

signals:
    void sendMessage(QString message);
};

#endif // JOINLOBBYSCREEN_H
