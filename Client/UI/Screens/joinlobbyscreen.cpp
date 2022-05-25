#include "joinlobbyscreen.h"

JoinLobbyScreen::JoinLobbyScreen(QWidget *parent)
    : Screen{parent} {
    setPadding(25);
    setSpacing(25);

    // Instruction label
    label = new CustomLabel("Join Lobby", this);

    // Lobby ID input
    lobbyIDInput = new CustomLineEdit(this);
    lobbyIDInput->setPlaceholderText("Lobby ID");
    lobbyIDInput->setValidator(new QIntValidator(0, 9999, this));
    lobbyIDInput->setAlignment(Qt::AlignCenter);
    connect(lobbyIDInput, &QLineEdit::returnPressed, this, &JoinLobbyScreen::onJoinButtonClicked);

    // Back Button
    backButton = new CustomPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);

    // Join Button
    joinButton = new CustomPushButton("Join Lobby", this);
    connect(joinButton, &QPushButton::clicked, this, &JoinLobbyScreen::onJoinButtonClicked);
}

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Label
    int labelWidth = this->width(), labelHeight = this->height() * 0.13;
    int labelX = 0, labelY = this->height() / 4 - labelHeight / 2;
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Back Button
    int backButtonX = this->getPadding(), backButtonY = this->getPadding();
    int backButtonWidth = this->getAvaliableWidth() * 0.08, backButtonHeight = this->getAvaliableHeight() * 0.08;
    backButton->setGeometry(backButtonX, backButtonY, backButtonWidth, backButtonHeight);

    // Lobby ID Input
    int inputWidth = this->getAvaliableWidth() * 0.5, inputHeight = this->getAvaliableHeight() * 0.15;
    int lobbyIDInputX = (this->getAvaliableWidth()  - inputWidth) / 2, lobbyIDInputY = (this->getAvaliableHeight()) / 2;
    lobbyIDInput->setGeometry(lobbyIDInputX, lobbyIDInputY, inputWidth, inputHeight);

    // Join Button
    int joinButtonWidth = this->getAvaliableWidth() * 0.25, joinButtonHeight = this->getAvaliableHeight() * 0.15;
    int joinButtonX =  (this->getAvaliableWidth() - joinButtonWidth) / 2, joinButtonY = lobbyIDInputY + inputHeight + this->getSpacing();
    joinButton->setGeometry(joinButtonX, joinButtonY, joinButtonWidth, joinButtonHeight);
}

void JoinLobbyScreen::onJoinButtonClicked() {
    QString newLobbyID = "", nickname = "";
    newLobbyID = lobbyIDInput->text();
    nickname = NicknameInputDialog::getNickname(this);

    if (newLobbyID.length() == 4 && !nickname.isEmpty()) {
        emit sendRequestMessage("type:joinLobbyRequest;payLoad:" + newLobbyID + ";nickname:" + nickname);
    } else {
        QMessageBox::warning(this, "Error", "Please fill in all fields correctly.");
    }
}
