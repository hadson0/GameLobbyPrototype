#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <QApplication>
#include <QPushButton>

#include "screen.h"
#include "UI/Components/customlabel.h"

class SelectionScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    QPushButton *createLobbyButton, *joinLobbyButton;
    QPushButton *backButton;

    void resizeEvent(QResizeEvent *event);

public:
    SelectionScreen(QWidget *parent);

public slots:
    void onCreateLobbyCklicked();
    void onJoinLobbyButtonClicked();
};

#endif // SELECTIONSCREEN_H
