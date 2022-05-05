#include "mainmenuscreen.h"

MainMenuScreen::MainMenuScreen(QWidget *parent)
    : Screen(parent) {
    // Game Title Label
    label = new CustomLabel("Game Lobby Prototype", this);

    // Play Button
    playButton = new QPushButton("Play", this);
    connect(playButton, &QPushButton::clicked, this, &MainMenuScreen::onPlayButtonPressed);

    // Quit Button
    quitButton = new QPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, this, &Screen::quitApplicationRequest);
}

void MainMenuScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Label proprieties
    int spacing = this->height() * 0.15;
    int labelWidth = this->width(), labelHeight = this->height() * 0.10;
    int labelX = 0, labelY = this->height()/2 - spacing - labelHeight;
    label->setFontSize(labelHeight * 0.85);
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Button proprieties
    spacing = this->height() * 0.015;
    int buttonWidth = this->width()/3, buttonHeight = this->height() * 0.15;
    int buttonX = (this->width()/2) - (buttonWidth/2);
    int buttonY = (this->height()/2);

    // Play Button
    playButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Quit Button
    buttonY += buttonHeight + spacing;
    quitButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

void MainMenuScreen::onPlayButtonPressed() {
    emit displayMenuScreenRequest("SelectionScreen");
}
