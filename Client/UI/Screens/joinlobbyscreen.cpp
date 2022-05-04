#include "joinlobbyscreen.h"

JoinLobbyScreen::JoinLobbyScreen(GameManager *gameManager, QWidget *parent)
    : Screen{parent}, gameManager(gameManager) {
    // Instruction label
    label = new CustomLabel("Lobby Code", this);

    // Lobby ID Input
    lobbyIDInputEdit = new CustomLineEdit(this);
    lobbyIDInputEdit->setValidator(new QIntValidator(0, 9999, this));
    lobbyIDInputEdit->setAlignment(Qt::AlignCenter);
    connect(lobbyIDInputEdit, &CustomLineEdit::onEnterPressed, this, &JoinLobbyScreen::onJoinButtonClicked);

    // Back Button
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &JoinLobbyScreen::onBackButtonClicked);

    // Join Button
    joinButton = new QPushButton("Join Lobby", this);
    connect(joinButton, &QPushButton::clicked, this, &JoinLobbyScreen::onJoinButtonClicked);
}

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    int spacing = 25;

    // Lobby ID Input
    int inputWidth = this->width() * 0.5, inputHeight = this->height() * 0.2;
    int fontSize = inputHeight * 0.85;
    int inputX = (this->width() / 2) - (inputWidth / 2), inputY = (this->height() / 2) - (inputHeight / 2);
    lobbyIDInputEdit->setGeometry(inputX, inputY, inputWidth, inputHeight);
    QFont font = lobbyIDInputEdit->font();
    font.setPixelSize(fontSize);
    lobbyIDInputEdit->setFont(font);

    // Instruction label
    int labelWidth = this->width(), labelHeight = this->height() * 0.10;
    int labelX = 0, labelY = this->height()/2 - spacing - labelHeight - (inputHeight / 2);
    label->setFontSize(labelHeight * 0.85);
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Back Button
    int backButtonWidth = this->width() * 0, backButtonHeight = 0;
    int backButtonX = 0, backButtonY = 0;
    backButton->setGeometry(backButtonX, backButtonY, backButtonWidth, backButtonHeight);

    // Join Button
    int joinButtonWidth = this->width() * 0.2, joinButtonHeight = this->height() * 0.1;
    int joinButtonX =  (this->width() / 2) - (joinButtonWidth / 2), joinButtonY = inputY + inputHeight + spacing;
    joinButton->setGeometry(joinButtonX, joinButtonY, joinButtonWidth, joinButtonHeight);
}

void JoinLobbyScreen::onBackButtonClicked() {
    onScreenChanged();
    emit screenChanged("SelectionScreen");
}

void JoinLobbyScreen::onJoinButtonClicked() {
    QString lobbyID = QString();
    lobbyID = lobbyIDInputEdit->text();

    qDebug() << lobbyID;

    if (lobbyID.length() == 4) {
        gameManager->joinLobbyRequest(lobbyID);
        onScreenChanged();
        emit screenChanged("LobbyScreen");
    }
}

void JoinLobbyScreen::onLobbyIDChanged(QString newLobbyID) {
    onScreenChanged();
    emit screenChanged("LobbyScreen:" + newLobbyID);
}
