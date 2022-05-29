#include "gamemanager.h"

GameManager *GameManager::instance = nullptr;

GameManager::GameManager(QObject *parent)
    : QObject{parent}, clientID(""), lobbyID("") {
    messageProcessHandler = new MessageProcessHandler(this);

    // Socket related message process handler connections
    connect(this, &GameManager::processSocketMessage, messageProcessHandler, &MessageProcessHandler::processSocketMessage);
    connect(messageProcessHandler, &MessageProcessHandler::setClientID, this, &GameManager::setClientID);
    connect(messageProcessHandler, &MessageProcessHandler::newLobby, this, &GameManager::onLobbyJoined);
    connect(messageProcessHandler, &MessageProcessHandler::userListUpdated, this, &GameManager::setUserList);
    connect(messageProcessHandler, &MessageProcessHandler::readyListUpdated, this, &GameManager::setReadyList);
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

QStringList GameManager::getUserList() { return userMap.keys(); }


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

void GameManager::setUserList(QStringList newUserList) {
    // This if statement prevents an unecessary signal emission
    QStringList clientList = getUserList();
    if (clientList != newUserList) {
        // Reset the client map, setting all the clients ready status to false
        userMap.clear();
        for (const QString &clientID : newUserList) {
                userMap[clientID] = false;
        }
        emit userListChanged(newUserList);
    }
}

void GameManager::setReadyList(QStringList readyUsers) {
    QMap<QString, bool>::iterator it = userMap.begin();
    for (; it != userMap.end(); it++) {
        it.value() = readyUsers.contains(it.key());
    }

    emit readyListChanged(readyUsers);
}

void GameManager::toggleReadyRequest() {
    int ready = !userMap[nickname]; // 0 = false  1 = true
    emit newMessageReadyToSend("type:setReady;payLoad:" + QString::number(ready) + ";lobbyID:" + lobbyID + ";senderID:" + clientID);
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
    setUserList(newUserList);
    emit inGameLobby();
}

void GameManager::leaveLobby() {
    nickname = lobbyID = "";
    userMap.clear();
}
