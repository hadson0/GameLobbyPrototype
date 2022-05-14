#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}, clientID(QString()), clientList(QStringList()), lobbyID(QString()) {
    messageProcessHandler = new MessageProcessHandler(this);

    // Socket related message process handler connections
    connect(this, &GameManager::processSocketMessage, messageProcessHandler, &MessageProcessHandler::processSocketMessage);
    connect(messageProcessHandler, &MessageProcessHandler::uniqueIDRegistration, this, &GameManager::registerUniqueID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::onLobbyJoined);
    connect(messageProcessHandler, &MessageProcessHandler::lobbyListUpdated, this, &GameManager::setClientList);
    connect(messageProcessHandler, &MessageProcessHandler::newLobbyMessageRecieved, this, &GameManager::newLobbyMessageRecieved);

    // Screen related message process handler connections
    connect(this, &GameManager::processScreenMessage, messageProcessHandler, &MessageProcessHandler::processScreenMessage);
    connect(messageProcessHandler, &MessageProcessHandler::createLobbyRequest, this, &GameManager::onCreateLobbyRequested);
    connect(messageProcessHandler, &MessageProcessHandler::joinLobbyRequest, this, &GameManager::onJoinLobbyRequested);
    connect(messageProcessHandler, &MessageProcessHandler::sendLobbyMessageRequest, this, &GameManager::onSendLobbyMessageRequested);
}

GameManager::~GameManager() {
    messageProcessHandler->deleteLater();
}

QString GameManager::getLobbyID() {
    return lobbyID;
}

QStringList GameManager::getClientsInLobby() {
    return clientList;
}

void GameManager::onCreateLobbyRequested() {
    emit newMessageReadyToSend("type:createGame;payLoad:0;senderID:" + clientID);
}

void GameManager::onJoinLobbyRequested(QString targetLobbyID) {
    emit newMessageReadyToSend("type:joinGame;payLoad:" + targetLobbyID + ";senderID:" + clientID);
}

void GameManager::onSendLobbyMessageRequested(QString message) {
    emit newMessageReadyToSend("type:message;payLoad:" + message + ";lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::setLobbyID(QString newLobbyID) {
    // This if statement prevents an unecessary signal emission
    if (lobbyID != newLobbyID) {
        lobbyID = newLobbyID;

        if (lobbyID.isEmpty())
            emit lobbyLeft();
        else
            emit lobbyIDChanged(newLobbyID);
    }
}

void GameManager::setClientList(QStringList newClientList) {
    // This if statement prevents an unecessary signal emission
    if (clientList != newClientList) {
        clientList = newClientList;
        emit clientListChanged(clientList);
    }
}

void GameManager::registerUniqueID(QString uniqueID) {
    clientID = uniqueID;
}

void GameManager::onLobbyJoined(QString lobbyID, QStringList clients) {
    setLobbyID(lobbyID);
    setClientList(clients);
    emit inGameLobby();
}


