    #include "selectionscreen.h"

SelectionScreen::SelectionScreen(QWidget *parent)
    : Screen(parent) {
    // Game Title Label
    label = new CustomLabel("Game Lobby Prototype", this);

    // Create Lobby Button
    createLobbyButton = new QPushButton("Create Lobby", this);
    connect(createLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onCreateLobbyCklicked);

    // Join Lobby Button
    joinLobbyButton = new QPushButton("Join Lobby", this);    
    connect(joinLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onJoinLobbyButtonClicked);

    // Back Button
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);
}

void SelectionScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Label proprieties
    int spacing = this->height() * 0.15;
    int labelWidth = this->width(), labelHeight = this->height() * 0.10;
    int labelX = 0, labelY = this->height()/2 - spacing - labelHeight;

    // Game Title Label
    label->setFontSize(labelHeight * 0.85);
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Button proprieties
    spacing = this->height() * 0.015;
    int buttonWidth = this->width()/3, buttonHeight = this->height() * 0.15;
    int buttonX = (this->width()/2) - (buttonWidth/2);
    int buttonY = (this->height()/2);

    // Create Lobby Button
    createLobbyButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Join Lobby Button
    buttonY += buttonHeight + spacing;
    joinLobbyButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Back Button
    buttonY += buttonHeight + spacing;
    backButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

void SelectionScreen::onCreateLobbyCklicked() {
    emit sendRequestMessage("type:createLobbyRequest;payload:0");
}

void SelectionScreen::onJoinLobbyButtonClicked() {
    emit displayMenuScreenRequest("JoinLobbyScreen");
}
