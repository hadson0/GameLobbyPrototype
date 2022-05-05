#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include <QPushButton>
#include <QLabel>

#include "screen.h"
#include "UI/Components/customlabel.h"

class MainMenuScreen : public Screen {
    Q_OBJECT

    CustomLabel *label;
    QPushButton *playButton, *quitButton;

    void resizeEvent(QResizeEvent *event);

public:
    MainMenuScreen(QWidget *parent);

public slots:
    void onPlayButtonPressed();
};

#endif // MAINMENUSCREEN_H
