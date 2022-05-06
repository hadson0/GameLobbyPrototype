#include "lobbyscreen.h"

LobbyScreen::LobbyScreen(QString lobbyID, QWidget *parent)
    : Screen{parent}, lobbyID(lobbyID) {
    setPadding(25);

    // Back Button
    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &Screen::backRequest);

    // Lobby ID Label    
    lobbyIDLabel = new CustomLabel("Lobby Code: " + lobbyID, this);

    // Client List View
    clientListView = new ClientListView(this);

    // Chat Frame
    chatFrame = new ChatFrame(this);
    connect(chatFrame, &ChatFrame::sendMessage, this, &LobbyScreen::requestSendLobbyMessage);
    connect(this, &LobbyScreen::newMessageRecieved, chatFrame, &ChatFrame::onMessageRecieved);
}

void LobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    int avaliableWidht = this->width() - 2 * padding, avaliableHeight = this->height() - 2 * padding;

    // Back Button
    int backButtonX = padding, backButtonY = padding;
    int backButtonWidth = avaliableWidht * 0.08, backButtonHeight = avaliableHeight * 0.08;
    backButton->setGeometry(backButtonX, backButtonY, backButtonWidth, backButtonHeight);

    // Lobby ID Label
    int lobbyIDLabelX = backButtonX + backButtonWidth, lobbyIDLabelY = backButtonY;
    int lobbyIDLabelWidth = avaliableWidht - lobbyIDLabelX, lobbyIDLabelHeight = backButtonHeight;
    lobbyIDLabel->setFontSize(lobbyIDLabelHeight * 0.85);
    lobbyIDLabel->setGeometry(lobbyIDLabelX, lobbyIDLabelY, lobbyIDLabelWidth, lobbyIDLabelHeight);

    // Client List View
    int clientListViewX = padding, clientListViewY = padding + 75;
    int clientListViewWidth = (avaliableWidht - padding) * 0.4, clientListViewHeight = avaliableHeight - 75;
    clientListView->setGeometry(clientListViewX, clientListViewY, clientListViewWidth, clientListViewHeight);

    // Chat Frame
    int chatFrameX = clientListViewWidth + 2 * padding, chatFrameY = clientListViewY;
    int chatFrameWidth = (avaliableWidht - padding) * 0.6, chatFrameHeight = clientListViewHeight;
    chatFrame->setGeometry(chatFrameX, chatFrameY, chatFrameWidth, chatFrameHeight);
}


void LobbyScreen::requestSendLobbyMessage(QString message) {
    emit sendRequestMessage("type:sendLobbyMessageRequest;payLoad:" + message);
}
