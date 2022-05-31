#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent} {
    webSocketHandler = WebSocketHandler::getInstance(this);
    messageProcessorHandler = new MessageProcessHandler(this);

    //Coneccts signals and slots
    connect(webSocketHandler, &WebSocketHandler::newMessageToProcess, messageProcessorHandler, &MessageProcessHandler::processSocketMessage);
    connect(webSocketHandler, &WebSocketHandler::clientDisconnected, this, &GameManager::onClientDisconnected);

    connect(messageProcessorHandler, &MessageProcessHandler::toggleReadyRequest, this, &GameManager::toggleReadyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::createLobbyRequest, this, &GameManager::createLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::joinLobbyRequest, this, &GameManager::joinLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::quitLobbyRequest, this, &GameManager::quitLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::messageLobbyRequest, this, &GameManager::messageLobbyRequest);
}

// Generates a QString composed of 4 random numbers. Ex.: "1234"
QString GameManager::generateRandomID() {
    std::random_device rd;
    std:: default_random_engine generator(rd());
    std::uniform_int_distribution<int> idGenerator(1000, 9999);
    return QString::number(idGenerator(generator));
}

void GameManager::createLobbyRequest(QString clientID, QString nickname) {
    QString newLobbyID = generateRandomID();

    // Make surte that the generated ID is unique
    QStringList existingKeys = lobbyMap.keys();
    for (; existingKeys.contains(newLobbyID); newLobbyID = generateRandomID());

    // Registers the new lobby
    Lobby *newLobby = new Lobby(newLobbyID, this);
    connect(newLobby, &Lobby::userListChanged, this, &GameManager::onUserListChanged);
    connect(newLobby, &Lobby::readyListChanged, this, &GameManager::onReadyListChanged);

    newLobby->addUser(clientID, nickname);
    lobbyMap[newLobbyID] = newLobby;
    clientLobbyMap[clientID] = newLobby;

    // Sends the lobby ID and the user list to the client
    webSocketHandler->sendTextMessage("type:newLobbyCreated;payLoad:" + newLobbyID + ";userList:" + newLobby->getUsersToStr(), clientID);

    qDebug() << "New Lobby created, ID: " << newLobbyID;
}

void GameManager::joinLobbyRequest(QString lobbyID, QString clientID, QString nickname) {
    if (lobbyMap.contains(lobbyID)) {
        if (!lobbyMap[lobbyID]->containsNickname(nickname)) {
            Lobby *lobby = lobbyMap[lobbyID];
            lobby->addUser(clientID, nickname);
            clientLobbyMap[clientID] = lobby;

            // Informs the client that it was a success
            webSocketHandler->sendTextMessage("type:joinSuccess;payLoad:" + lobbyID  + ";userList:" + lobby->getUsersToStr() , clientID);
        } else {
            // Informs the client that an error has occurred
            webSocketHandler->sendTextMessage("type:error;payLoad:existingNickError", clientID);
        }
    } else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:error;payLoad:joinError", clientID);
    }
}

void GameManager::quitLobbyRequest(QString lobbyID, QString clientID) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        lobby->removeUser(clientID);
        clientLobbyMap.remove(clientID);
    } else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:error;payLoad:quitError", clientID);
    }
}

void GameManager::messageLobbyRequest(QString message, QString lobbyID, QString clientID) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        QString senderNick = lobby->getUserNick(clientID);

        // Sends the message to all the clients in the lobby
        webSocketHandler->sendTextMessage("type:lobbyMessage;payLoad:" + message + ";senderNick:" + senderNick, lobby->getClientList());
    } else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:error;payLoad:lobbyMessageError", clientID);
    }
}

void GameManager::toggleReadyRequest(QString lobbyID, QString clientID) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        lobby->toggleReady(clientID);
    }
}

void GameManager::onUserListChanged(QString users, QStringList clientList) {
    // If there is clients in lobby
    if (!users.isEmpty() && !clientList.isEmpty()) {
        // Update the user list to all the clients in the lobby
         webSocketHandler->sendTextMessage("type:updatedUserList;payLoad:0;userList:" + users, clientList);
    } else {
        try {
            // Delete the lobby
            Lobby *lobby = qobject_cast<Lobby *>(sender());
            QString lobbyID = lobby->getID();
            lobbyMap[lobbyID]->deleteLater();
            lobbyMap.remove(lobbyID);
        } catch (...) {
            qDebug() << "Error deleting lobby";
        }
    }
}

void GameManager::onReadyListChanged(QString readyUSers, QStringList clientList) {
    // Update the ready user list to all the clients in the lobby
    webSocketHandler->sendTextMessage("type:updatedReadyUserList;payLoad:0;userList:" + readyUSers, clientList);
}

void GameManager::onClientDisconnected(QString clientID) {
    if (clientLobbyMap.contains(clientID)) { // If the client was in a lobby
        clientLobbyMap[clientID]->removeUser(clientID); // Exits the lobby
        clientLobbyMap.remove(clientID);
    }
}
