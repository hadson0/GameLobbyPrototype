#include "joinlobbyscreen.h"

JoinLobbyScreen::JoinLobbyScreen(QWidget *parent)
    : Screen{parent} {
    setPadding(25);
    setSpacing(25);

    // Instruction label
    label = new CustomLabel("Lobby Code", this);

    // Lobby ID Input
    lobbyIDInputEdit = new CustomLineEdit(this);
    lobbyIDInputEdit->setValidator(new QIntValidator(0, 9999, this));
    lobbyIDInputEdit->setAlignment(Qt::AlignCenter);
    connect(lobbyIDInputEdit, &QLineEdit::returnPressed, this, &JoinLobbyScreen::onJoinButtonClicked);

    // Back Button
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);

    // Join Button
    joinButton = new QPushButton("Join Lobby", this);
    connect(joinButton, &QPushButton::clicked, this, &JoinLobbyScreen::onJoinButtonClicked);
}

void JoinLobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    int avaliableWidht = this->width() - 2 * padding, avaliableHeight = this->height() - 2 * padding;

    // Back Button
    int backButtonX = padding, backButtonY = padding;
    int backButtonWidth = avaliableWidht * 0.08, backButtonHeight = avaliableHeight * 0.08;
    backButton->setGeometry(backButtonX, backButtonY, backButtonWidth, backButtonHeight);

    // Lobby ID Input
    int inputWidth = avaliableWidht * 0.5, inputHeight = avaliableHeight * 0.2;
    int fontSize = inputHeight * 0.85;
    int inputX = (avaliableWidht / 2) - (inputWidth / 2), inputY = (avaliableHeight / 2) - (inputHeight / 2);
    lobbyIDInputEdit->setGeometry(inputX, inputY, inputWidth, inputHeight);
    QFont font = lobbyIDInputEdit->font();
    font.setPixelSize(fontSize);
    lobbyIDInputEdit->setFont(font);

    // Instruction label
    int labelWidth = avaliableWidht, labelHeight = avaliableHeight * 0.10;
    int labelX = 0, labelY = avaliableHeight/2 - spacing - labelHeight - (inputHeight / 2);
    label->setFontSize(labelHeight * 0.85);
    label->setGeometry(labelX, labelY, labelWidth, labelHeight);

    // Join Button
    int joinButtonWidth = avaliableWidht * 0.2, joinButtonHeight = avaliableHeight * 0.1;
    int joinButtonX =  (avaliableWidht / 2) - (joinButtonWidth / 2), joinButtonY = inputY + inputHeight + spacing;
    joinButton->setGeometry(joinButtonX, joinButtonY, joinButtonWidth, joinButtonHeight);
}

void JoinLobbyScreen::onJoinButtonClicked() {
    QString newLobbyID = QString();
    newLobbyID = lobbyIDInputEdit->text();

    qDebug() << newLobbyID;

    if (newLobbyID.length() == 4) {
        emit sendRequestMessage("type:joinLobbyRequest;payLoad:" + newLobbyID);
    }
}
