#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}, clientID(QString()), clientList(QStringList()), lobbyID(QString()) {
    messageProcessHandler = new MessageProcessHandler(this);

    connect(messageProcessHandler, &MessageProcessHandler::uniqueIDRegistration, this, &GameManager::registerUniqueID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::onLobbyJoined);
    connect(messageProcessHandler, &MessageProcessHandler::lobbyListUpdated, this, &GameManager::setClientList);
    connect(messageProcessHandler, &MessageProcessHandler::newLobbyMessage, this, &GameManager::newLobbyMessage);
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

void GameManager::createGameRequest() {
    emit newMessageReadyToSend("type:createGame;payLoad:0;senderID:" + clientID);
}

void GameManager::joinLobbyRequest(QString targetLobbyID) {
    emit newMessageReadyToSend("type:joinGame;payLoad:" + targetLobbyID + ";senderID:" + clientID);
}

void GameManager::sendMessageToLobby(QString message) {
    emit newMessageReadyToSend("type:message;payLoad:" + message + ";lobbyID:" + lobbyID + ";senderID:" + clientID);
}

void GameManager::setLobbyID(QString newLobbyID) {
    // This if statement prevents an unecessary signal emission
    if (lobbyID != newLobbyID) {
        lobbyID = newLobbyID;
        emit lobbyIDChanged(newLobbyID);
    }
}

void GameManager::setClientList(QStringList newClientList) {
    // This if statement prevents an unecessary signal emission
    if (clientList != newClientList) {
        clientList = newClientList;
        emit clientsInLobbyChanged();
    }
}

void GameManager::processSocketMessage(QString message) {
    messageProcessHandler->processMessage(message);
}

void GameManager::registerUniqueID(QString uniqueID) {
    qDebug() << "Client App: unique ID received " << uniqueID;
    clientID = uniqueID;
}

void GameManager::onLobbyJoined(QString lobbyID, QStringList clients) {
    setLobbyID(lobbyID);
    setClientList(clients);
    emit inGameLobby();
}


