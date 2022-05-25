#include "lobby.h"

Lobby::Lobby(QString lobbyID, QObject *parent)
    : QObject{parent} , lobbyID(lobbyID) {}

// Registers the client if it isn't registered and resets all the ready status
void Lobby::addClient(QString clientID, QString nickname) {
    // Adds the client
    if (!clientMap.contains(clientID)) {
        User *newUser = new User(clientID, nickname, this);
        newUser->setReady(false);
        clientMap[clientID] = newUser;
    }

    // Set all the ready status to false
    for (const QString &client : getClientList()) {
        clientMap[client]->setReady(false);
    }

    emit clientReadyChanged();
}

// Remove the client from the lobby and resets all the ready status
void Lobby::removeClient(QString clientID) {
    // removes the client
    if (clientMap.contains(clientID)) {
        clientMap.remove(clientID);
    }

    // Set all the ready status to false
    for (const QString &client : getClientList()) {
        clientMap[client]->setReady(false);
    }

    emit clientReadyChanged();
}


// Returns a QStringList containing all the clientsIDs
QStringList Lobby::getClientList() {
    return clientMap.keys();
}

// Returns a QString containing the clients information. Ex.: 1234:hadson0,5678:whoamI,4312:user_1
QString Lobby::getClientsInfo() {
    QString clientsInfo;

    QMap<QString, User *>::iterator it = clientMap.begin();
    for (; it != clientMap.end(); it++) {
        clientsInfo.append(it.key() + ":" + it.value()->getNickname() + ",");
    }
    clientsInfo.chop(1);

    return clientsInfo;
}

QStringList Lobby::getReadyClientIDList() {
    QStringList readyClientsList;

    QMap<QString, User *>::iterator it = clientMap.begin();
    for (; it != clientMap.end(); it++) {
        if (it.value()->isReady()) { // If the client is ready
            readyClientsList.append(it.key());
        }
    }

    return readyClientsList;
}

QString Lobby::getReadyListToStr() {
    QString readyClients;

    for (const QString &clientID : getReadyClientIDList()) {
        readyClients.append(clientID + ",");
    }
    readyClients.chop(1);

    return readyClients;
}

void Lobby::setReady(QString clientID, bool ready) {
    if (clientMap.contains(clientID)) {
        clientMap[clientID]->setReady(ready);

        emit clientReadyChanged();
    }
}

