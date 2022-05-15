#include "joinlobbyscreen.h"

JoinLobbyScreen::JoinLobbyScreen(QWidget *parent)
    : Screen{parent} {
    setPadding(25);
    setSpacing(25);

    // Instruction label
    instructionLabel = new CustomLabel("Lobby ID", this);

    // Lobby ID Input
    lobbyIDInputEdit = new QLineEdit(this);
    lobbyIDInputEdit->setValidator(new QIntValidator(0, 9999, this));
    lobbyIDInputEdit->setAlignment(Qt::AlignCenter);
    connect(lobbyIDInputEdit, &QLineEdit::returnPressed, this, &JoinLobbyScreen::onJoinButtonClicked);

    // Back Button
    backButton = new CustomPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);

    // Join Button
    joinButton = new CustomPushButton("Join Lobby", this);
    connect(joinButton, &QPushButton::clicked, this, &JoinLobbyScreen::onJoinButtonClicked);
}

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Back Button
    int backButtonX = this->getPadding(), backButtonY = this->getPadding();
    int backButtonWidth = this->getAvaliableWidth() * 0.08, backButtonHeight = this->getAvaliableHeight() * 0.08;
    backButton->setGeometry(backButtonX, backButtonY, backButtonWidth, backButtonHeight);

    // Lobby ID Input
    int inputWidth = this->getAvaliableWidth() * 0.5, inputHeight = this->getAvaliableHeight() * 0.2;
    int inputX = (this->getAvaliableWidth()  - inputWidth) / 2, inputY = (this->getAvaliableHeight() - inputHeight) / 2;
    lobbyIDInputEdit->setGeometry(inputX, inputY, inputWidth, inputHeight);
    QFont font = lobbyIDInputEdit->font();
    font.setPixelSize(inputHeight * 0.85);
    lobbyIDInputEdit->setFont(font);


    // Instruction label
    int labelWidth = this->getAvaliableWidth(), labelHeight = this->getAvaliableHeight() * 0.12;
    int labelX = 0, labelY = (this->getAvaliableHeight() - inputHeight) / 2 - this->getSpacing() - labelHeight;
    instructionLabel->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Join Button
    int joinButtonWidth = this->getAvaliableWidth() * 0.25, joinButtonHeight = this->getAvaliableHeight() * 0.15;
    int joinButtonX =  (this->getAvaliableWidth() - joinButtonWidth) / 2, joinButtonY = inputY + inputHeight + this->getSpacing();
    joinButton->setGeometry(joinButtonX, joinButtonY, joinButtonWidth, joinButtonHeight);
}

void JoinLobbyScreen::onJoinButtonClicked() {
    QString newLobbyID = "";
    newLobbyID = lobbyIDInputEdit->text();

    if (newLobbyID.length() == 4) {
        emit sendRequestMessage("type:joinLobbyRequest;payLoad:" + newLobbyID);
    }
}
