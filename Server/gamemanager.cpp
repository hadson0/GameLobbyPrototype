#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent} {
    webSocketHandler = new WebSocketHandler(this);
    messageProcessorHandler = new MessageProcessHandler(this);

    //Coneccts signals and slots
    connect(webSocketHandler, &WebSocketHandler::newMessageToProcess, messageProcessorHandler, &MessageProcessHandler::processSocketMessage);
    connect(messageProcessorHandler, &MessageProcessHandler::setReadyRequest, this, &GameManager::setReadyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::createLobbyRequest, this, &GameManager::createLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::joinLobbyRequest, this, &GameManager::joinLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::quitLobbyRequest, this, &GameManager::quitLobbyRequest);
    connect(messageProcessorHandler, &MessageProcessHandler::messageLobbyRequest, this, &GameManager::messageLobbyRequest);
}

GameManager::~GameManager() {
    // Guarantees that memory will be deallocated
    webSocketHandler->deleteLater();
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
    Lobby *lobby = new Lobby(newLobbyID, this);
    connect(lobby, &Lobby::clientReadyChanged, this, &GameManager::onClientReadyChanged);

    lobby->addClient(clientID, nickname);
    lobbyMap[newLobbyID] = lobby;

    // Sends the lobby ID and the client list to the client
    webSocketHandler->sendTextMessage("type:newLobbyCreated;payLoad:" + newLobbyID + ";clientList:" + lobby->getClientsInfo(), clientID);

    qDebug() << "New Lobby created, ID: " << newLobbyID;
}

void GameManager::joinLobbyRequest(QString lobbyID, QString clientID, QString nickname) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        lobby->addClient(clientID, nickname);

        // Informs the client that it was a success
        webSocketHandler->sendTextMessage("type:joinSuccess;payLoad:" + lobbyID  + ";clientList:" + lobby->getClientsInfo() , clientID);

        // Updates the client list to all the clients in the lobby
        webSocketHandler->sendTextMessageToClients("type:updatedClientList;payLoad:0;clientList:" + lobby->getClientsInfo(), lobby->getClientList());
    } else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:joinError;payLoad:DNE", clientID);
    }
}

void GameManager::quitLobbyRequest(QString lobbyID, QString clientID) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        lobby->removeClient(clientID);

        // Updates the client list to all the clients in the lobby
        webSocketHandler->sendTextMessageToClients("type:updatedClientList;payLoad:0;clientList:" + lobby->getClientsInfo(), lobby->getClientList());
    } else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:quitError;payLoad:DNE", clientID);
    }
}

void GameManager::messageLobbyRequest(QString message, QString lobbyID, QString clientID) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];

        // Sends the message to all the clients in the lobby
        webSocketHandler->sendTextMessageToClients("type:lobbyMessage;payLoad:" + message + ";senderID:" + clientID, lobby->getClientList());
    }else {
        // Informs the client that an error has occurred
        webSocketHandler->sendTextMessage("type:lobbyMessageError;payLoad:DNE", clientID);
    }
}

void GameManager::setReadyRequest(QString lobbyID, QString clientID, bool ready) {
    // Checks if the lobby is registered
    if (lobbyMap.contains(lobbyID)) {
        Lobby *lobby = lobbyMap[lobbyID];
        lobby->setReady(clientID, ready);
    }
}

void GameManager::onClientReadyChanged() {
    // Gets the lobby that sent the signal using the sender function
    Lobby *lobby = qobject_cast<Lobby *>(sender());

    // Sends the message to all the clients in the lobby
    webSocketHandler->sendTextMessageToClients("type:updatedReadyClientList;payLoad:0;clientList:" + lobby->getReadyListToStr(), lobby->getClientList());
}
