#include "gamemanager.h"

GameManager *GameManager::instance = nullptr;

GameManager::GameManager(QObject *parent)
    : QObject{parent}, clientID(""), lobbyID("") {
    messageProcessHandler = new MessageProcessHandler(this);

    // Socket related message process handler connections
    connect(this, &GameManager::processSocketMessage, messageProcessHandler, &MessageProcessHandler::processSocketMessage);
    connect(messageProcessHandler, &MessageProcessHandler::setClientID, this, &GameManager::setClientID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::onLobbyJoined);
    connect(messageProcessHandler, &MessageProcessHandler::userListUpdated, this, &GameManager::userListChanged);
    connect(messageProcessHandler, &MessageProcessHandler::readyListUpdated, this, &GameManager::readyListChanged);
    connect(messageProcessHandler, &MessageProcessHandler::newLobbyMessageRecieved, this, &GameManager::newLobbyMessageRecieved);

    // Screen related message process handler connections
    connect(this, &GameManager::processScreenMessage, messageProcessHandler, &MessageProcessHandler::processScreenMessage);
    connect(messageProcessHandler, &MessageProcessHandler::connectToServerRequest, this, &GameManager::connectToServerRequest);
    connect(messageProcessHandler, &MessageProcessHandler::createLobbyRequest, this, &GameManager::createLobbyRequest);
    connect(messageProcessHandler, &MessageProcessHandler::joinLobbyRequest, this, &GameManager::joinLobbyRequested);
    connect(messageProcessHandler, &MessageProcessHandler::quitLobbyRequest, this, &GameManager::quitLobbyRequest);
    connect(messageProcessHandler, &MessageProcessHandler::sendLobbyMessageRequest, this, &GameManager::sendLobbyMessageRequested);
    connect(messageProcessHandler, &MessageProcessHandler::toggleReadyRequest, this, &GameManager::toggleReadyRequest);

    connect(messageProcessHandler, &MessageProcessHandler::error, this, &GameManager::error);
}

QString GameManager::getLobbyID() { return lobbyID; }


void GameManager::setClientID(QString clientID) {
    this->clientID = clientID;
    emit clientConnected();
}

void GameManager::setLobbyID(QString newLobbyID) {
    // This if statement prevents an unecessary signal emission
    if (lobbyID != newLobbyID) {
        lobbyID = newLobbyID;

        if (lobbyID.isEmpty()) {
            emit lobbyLeft();
        } else {
            emit lobbyIDChanged(newLobbyID);
        }
    }
}

void GameManager::toggleReadyRequest() {
    emit newMessageReadyToSend("type:toggleReady;payLoad:0;lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::createLobbyRequest(QString nickname) {
    this->nickname = nickname;
    emit newMessageReadyToSend("type:createGame;payLoad:0;senderID:" + clientID + ";nickname:" + nickname);
}

void GameManager::joinLobbyRequested(QString targetLobbyID, QString nickname) {
    this->nickname = nickname;
    emit newMessageReadyToSend("type:joinGame;payLoad:" + targetLobbyID + ";senderID:" + clientID + ";nickname:" + nickname);
}

void GameManager::sendLobbyMessageRequested(QString message) {
    emit newMessageReadyToSend("type:message;payLoad:" + message + ";lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::quitLobbyRequest() {
    emit newMessageReadyToSend("type:quitLobbyRequest;payLoad:0;lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::onLobbyJoined(QString lobbyID, QStringList newUserList) {
    setLobbyID(lobbyID);
    emit userListChanged(newUserList);
    emit joinedLobby();
}

void GameManager::leaveLobby() {
    nickname = lobbyID = "";
}
