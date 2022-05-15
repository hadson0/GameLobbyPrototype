#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}, clientID(""), lobbyID("") {
    messageProcessHandler = new MessageProcessHandler(this);

    // Socket related message process handler connections
    connect(this, &GameManager::processSocketMessage, messageProcessHandler, &MessageProcessHandler::processSocketMessage);
    connect(messageProcessHandler, &MessageProcessHandler::clientIDRegistration, this, &GameManager::registerClientID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::onLobbyJoined);
    connect(messageProcessHandler, &MessageProcessHandler::lobbyListUpdated, this, &GameManager::setClientList);
    connect(messageProcessHandler, &MessageProcessHandler::newLobbyMessageRecieved, this, &GameManager::newLobbyMessageRecieved);

    // Screen related message process handler connections
    connect(this, &GameManager::processScreenMessage, messageProcessHandler, &MessageProcessHandler::processScreenMessage);
    connect(messageProcessHandler, &MessageProcessHandler::createLobbyRequest, this, &GameManager::createLobbyRequest);
    connect(messageProcessHandler, &MessageProcessHandler::joinLobbyRequest, this, &GameManager::joinLobbyRequested);
    connect(messageProcessHandler, &MessageProcessHandler::sendLobbyMessageRequest, this, &GameManager::sendLobbyMessageRequested);
}

GameManager::~GameManager() {
    messageProcessHandler->deleteLater();
}

QString GameManager::getLobbyID() { return lobbyID; }

QStringList GameManager::getClientList() { return clientMap.keys(); }

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

void GameManager::setClientList(QStringList newClientList) {
    // This if statement prevents an unecessary signal emission
    QStringList clientList = getClientList();
    if (clientList != newClientList) {
        clientList = newClientList;
        emit clientListChanged(clientList);
    }
}

void GameManager::createLobbyRequest() {
    emit newMessageReadyToSend("type:createGame;payLoad:0;senderID:" + clientID);
}

void GameManager::joinLobbyRequested(QString targetLobbyID) {
    emit newMessageReadyToSend("type:joinGame;payLoad:" + targetLobbyID + ";senderID:" + clientID);
}

void GameManager::sendLobbyMessageRequested(QString message) {
    emit newMessageReadyToSend("type:message;payLoad:" + message + ";lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::onLobbyJoined(QString lobbyID, QStringList newClientList) {
    setLobbyID(lobbyID);
    setClientList(newClientList);
    emit inGameLobby();
}

void GameManager::registerClientID(QString uniqueID) {
    clientID = uniqueID;
}



