#include "mainmenuscreen.h"

MainMenuScreen::MainMenuScreen(QWidget *parent)
    : Screen(parent) {
    // Game Title Label
    label = new CustomLabel("Game Lobby Prototype", this);

    // Play Button
    playButton = new CustomPushButton("Play", this);
    connect(playButton, &QPushButton::clicked, this, &MainMenuScreen::onPlayButtonPressed);

    // Quit Button
    quitButton = new CustomPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, this, &Screen::quitAppRequest);
}

void MainMenuScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    this->setSpacing(this->height() * 0.015);

    // Label proprieties
    int labelWidth = this->width(), labelHeight = this->height() * 0.13;
    int labelX = 0, labelY = this->height() / 4 - labelHeight / 2;
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Button proprieties
    int buttonWidth = this->width() / 3, buttonHeight = this->height() * 0.15;
    int buttonX = (this->width() - buttonWidth) / 2, buttonY = this->height() / 2;

    // Play Button
    playButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Quit Button
    buttonY += buttonHeight + this->getSpacing();
    quitButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

void MainMenuScreen::onPlayButtonPressed() {
    emit menuScreenDisplayRequest("SelectionScreen");
}
