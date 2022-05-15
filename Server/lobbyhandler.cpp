#include "lobbyhandler.h"

LobbyHandler::LobbyHandler(QString lobbyID, QObject *parent)
    : QObject{parent} , lobbyID(lobbyID), clientMap(QMap<QString, bool>()) {}

// Registers the client if it isn't registered and resets all the ready status
void LobbyHandler::addClient(QString clientID) {
    // Add the client
    if (!clientMap.contains(clientID)) {
        clientMap[clientID] = false;
    }

    // Set all the ready status to false
    for (const QString &client : getClientList()) {
        clientMap[client] = false;
    }

    emit clientReadyChanged();
}


// Returns a QStringList containing all the clientsIDs
QStringList LobbyHandler::getClientList() {
    return clientMap.keys();
}

// Returns a QString containing all the clientsIDs, separated by ",". Ex.: 1234,5678,4312
QString LobbyHandler::getClientListToStr() {
    QString clientString;

    for (auto &client : getClientList()) {
        clientString.append(client + ",");
    }
    clientString.chop(1);

    return clientString;
}

QStringList LobbyHandler::getReadyClientsList() {
    QStringList readyClientsList;

    QMap<QString, bool>::iterator it = clientMap.begin();
    for (; it != clientMap.end(); it++) {
        if (it.value()) { // If the client is ready
            readyClientsList.append(it.key());
        }
    }

    return readyClientsList;
}

QString LobbyHandler::getReadyListToStr() {
    QString readyClients;

    for (const QString &clientID : getReadyClientsList()) {
        readyClients.append(clientID + ",");
    }
    readyClients.chop(1);

    return readyClients;
}

void LobbyHandler::setReady(QString clientID, bool ready) {
    if (clientMap.contains(clientID)) {
        clientMap[clientID] = ready;

        emit clientReadyChanged();
    }
}

