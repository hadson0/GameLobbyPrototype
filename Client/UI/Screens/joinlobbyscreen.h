#ifndef JOINLOBBYSCREEN_H
#define JOINLOBBYSCREEN_H

#include <QPushButton>
#include <QIntValidator>

#include "screen.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/customlineedit.h"

class JoinLobbyScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    QPushButton *joinButton, *backButton;
    CustomLineEdit *lobbyIDInputEdit;

    void resizeEvent(QResizeEvent *event);

public:
    explicit JoinLobbyScreen(QWidget *parent = nullptr);

public slots:
    void onJoinButtonClicked();
};

#endif // JOINLOBBYSCREEN_H
