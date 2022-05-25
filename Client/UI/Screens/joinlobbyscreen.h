#ifndef JOINLOBBYSCREEN_H
#define JOINLOBBYSCREEN_H

#include <QMessageBox>

#include "screen.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/custompushbutton.h"
#include "UI/Components/customlineedit.h"
#include "UI/Components/nicknameinputdialog.h"

class JoinLobbyScreen : public Screen {
    Q_OBJECT

    // Widgets
    CustomLabel *label;
    CustomPushButton *joinButton, *backButton;
    CustomLineEdit *lobbyIDInput;

    void resizeEvent(QResizeEvent *event);

public:
    explicit JoinLobbyScreen(QWidget *parent = nullptr);

public slots:
    void onJoinButtonClicked();
};

#endif // JOINLOBBYSCREEN_H
