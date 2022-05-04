    #include "selectionscreen.h"

SelectionScreen::SelectionScreen(GameManager *gameManager, QWidget *parent)
    : Screen(parent), gameManager(gameManager) {
    // Game Title Label
    label = new CustomLabel("Game Lobby Prototype", this);

    // Create Lobby Button
    createLobbyButton = new QPushButton("Create Lobby", this);
    connect(createLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onCreateLobbyButtonClicked);

    // Join Lobby Button
    joinLobbyButton = new QPushButton("Join Lobby", this);    
    connect(joinLobbyButton, &QPushButton::clicked, this, &SelectionScreen::onJoinLobbyButtonClicked);

    // Back Button
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &SelectionScreen::onBackButtonClicked);

    connect(gameManager, &GameManager::lobbyIDChanged, this, &SelectionScreen::onLobbyIDChanged);
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

void SelectionScreen::onCreateLobbyButtonClicked() {
    gameManager->createGameRequest();
}

void SelectionScreen::onJoinLobbyButtonClicked() {
    onScreenChanged();
    emit screenChanged("JoinLobbyScreen");
}

void SelectionScreen::onBackButtonClicked() {
    onScreenChanged();
    emit screenChanged("MainMenuScreen");
}

void SelectionScreen::onLobbyIDChanged(QString newLobbyID) {
    onScreenChanged();
    emit screenChanged("LobbyScreen:" + newLobbyID);
}
