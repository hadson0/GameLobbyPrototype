#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "screen.h"
#include "UI/Components/customlabel.h"
#include "UI/Components/custompushbutton.h"
#include "UI/Components/customlineedit.h"

class MainMenuScreen : public Screen {
    Q_OBJECT

    // Widgets
    CustomLabel *label;
    CustomPushButton *playButton, *quitButton;

    void resizeEvent(QResizeEvent *event);

public:
    MainMenuScreen(QWidget *parent);

signals:
    void connectToTheServerRequest();
};

#endif // MAINMENUSCREEN_H
