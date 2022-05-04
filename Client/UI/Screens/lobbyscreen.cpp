#include "lobbyscreen.h"

LobbyScreen::LobbyScreen(QString lobbyID, GameManager *gameManager, QWidget *parent)
    : Screen{parent}, padding(25), lobbyID(lobbyID), gameManager(gameManager) {
    // Lobby ID Label    
    lobbyIDLabel = new CustomLabel("Lobby Code: " + lobbyID, this);

    // Client List View
    clientListView = new ClientListView(this);

    // Chat Frame
    chatFrame = new ChatFrame(this);
    connect(chatFrame, &ChatFrame::sendMessage, gameManager, &GameManager::sendMessageToLobby);
    connect(gameManager, &GameManager::newLobbyMessage, chatFrame, &ChatFrame::onMessageRecieved);
}

void LobbyScreen::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    // Lobby ID Label
    int lobbyIDLabelX = padding, lobbyIDLabelY = padding;
    int lobbyIDLabelWidth = this->width() - 2 * padding, lobbyIDLabelHeight = this->height() * 0.05;
    lobbyIDLabel->setFontSize(lobbyIDLabelHeight * 0.85);
    lobbyIDLabel->setGeometry(lobbyIDLabelX, lobbyIDLabelY, lobbyIDLabelWidth, lobbyIDLabelHeight);

    // Client List View
    int clientListViewX = padding, clientListViewY = padding + 75;
    int clientListViewWidth = (this->width() - 3 * padding) * 0.4, clientListViewHeight = this->height() - padding - 100;
    clientListView->setGeometry(clientListViewX, clientListViewY, clientListViewWidth, clientListViewHeight);

    // Chat Frame
    int chatFrameX = clientListViewWidth + 2 * padding, chatFrameY = clientListViewY;
    int chatFrameWidth = (this->width() - 3 * padding) * 0.6, chatFrameHeight = clientListViewHeight;
    chatFrame->setGeometry(chatFrameX, chatFrameY, chatFrameWidth, chatFrameHeight);
}
