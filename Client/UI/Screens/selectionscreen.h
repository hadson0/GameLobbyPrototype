#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <QApplication>
#include <QPushButton>

#include "screen.h"
#include "Controllers/gamemanager.h"
#include "UI/Components/customlabel.h"

class SelectionScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    QPushButton *createLobbyButton, *joinLobbyButton;
    QPushButton *backButton;

    GameManager *gameManager;

    void resizeEvent(QResizeEvent *event);

public:
    SelectionScreen(GameManager *gameManager, QWidget *parent);

public slots:
    void onCreateLobbyButtonClicked();
    void onJoinLobbyButtonClicked();
    void onBackButtonClicked();

    void onLobbyIDChanged(QString newLobbyID);
};

#endif // SELECTIONSCREEN_H
