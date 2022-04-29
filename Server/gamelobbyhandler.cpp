#include "gamelobbyhandler.h"

GameLobbyHandler::GameLobbyHandler(QString lobbyID, QObject *parent)
    : QObject{parent} , lobbyID(lobbyID) {}

// Registers the client if it isn't registered
void GameLobbyHandler::addClient(QString clientID) {
    if (!clientList.contains(clientID))
        clientList.append(clientID);
}

// Returns a QString containing all the clientsIDs, separated by ",". Ex.: 1234,5678,4312
QString GameLobbyHandler::getClientListToString() {
    QString clientString;

    for (auto &client : clientList)
        clientString.append(client + ",");

    clientString.chop(1);

    return clientString;
}

// Returns a QStringList containing all the clientsIDs
QStringList GameLobbyHandler::getClientList() {
    return clientList;
}
