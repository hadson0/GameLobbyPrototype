    #include "selectionscreen.h"

SelectionScreen::SelectionScreen(QWidget *parent)
    : Screen(parent) {
    // Game Title Label
    label = new CustomLabel("Game Lobby Prototype", this);

    // Create Lobby Button
    createLobbyButton = new CustomPushButton("Create Lobby", this);
    connect(createLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onCreateLobbyCklicked);

    // Join Lobby Button
    joinLobbyButton = new CustomPushButton("Join Lobby", this);
    connect(joinLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onJoinLobbyButtonClicked);

    // Back Button
    backButton = new CustomPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);
}

void SelectionScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    this->setSpacing(this->height() * 0.015);

    // Label proprieties
    int labelWidth = this->width(), labelHeight = this->height() * 0.13;
    int labelX = 0, labelY = this->height() / 4 - labelHeight / 2;
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Button proprieties
    int buttonWidth = this->width() / 3, buttonHeight = this->height() * 0.15;
    int buttonX = (this->width() - buttonWidth) / 2, buttonY = this->height() / 2;

    // Create Lobby Button
    createLobbyButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Join Lobby Button
    buttonY += buttonHeight + this->getSpacing();
    joinLobbyButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // Back Button
    buttonY += buttonHeight + this->getSpacing();
    backButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

void SelectionScreen::onCreateLobbyCklicked() {
    emit sendRequestMessage("type:createLobbyRequest;payload:0");
}

void SelectionScreen::onJoinLobbyButtonClicked() {
    emit displayMenuScreenRequest("JoinLobbyScreen");
}
