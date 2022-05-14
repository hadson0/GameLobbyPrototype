#ifndef JOINLOBBYSCREEN_H
#define JOINLOBBYSCREEN_H

#include <QIntValidator>
#include <QLineEdit>

#include "screen.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/custompushbutton.h"

class JoinLobbyScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    CustomPushButton *joinButton, *backButton;
    QLineEdit *lobbyIDInputEdit;

    void resizeEvent(QResizeEvent *event);

public:
    explicit JoinLobbyScreen(QWidget *parent = nullptr);

public slots:
    void onJoinButtonClicked();
};

#endif // JOINLOBBYSCREEN_H
