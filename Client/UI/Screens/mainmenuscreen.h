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
    CustomLineEdit *nickInput;
    CustomPushButton *playButton, *quitButton;

    void resizeEvent(QResizeEvent *event);

public:
    MainMenuScreen(QWidget *parent);

public slots:
    void onPlayButtonPressed();
};

#endif // MAINMENUSCREEN_H
