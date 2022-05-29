#include "lobby.h"

Lobby::Lobby(QString lobbyID, QObject *parent)
    : QObject{parent} , lobbyID(lobbyID) {}

// Registers the user if it isn't registered and resets all the ready status
void Lobby::addUser(QString clientID, QString nickname) {
    // Adds the user
    if (!userMap.contains(clientID)) {
        User *newUser = new User(nickname, this);
        userMap[clientID] = newUser;
    }

    // Set all the ready status to false
    for (const QString &user : getClientList()) {
        if (userMap[user]->isReady()) {
            userMap[user]->toggleReady();
        }
    }

    emit readyListChanged(getReadyUsersStr(), getClientList());
}

// Remove the user from the lobby and resets all the ready status
void Lobby::removeUser(QString clientID) {
    // removes the user
    if (userMap.contains(clientID)) {
        userMap.remove(clientID);
    }

    // Set all the ready status to false
    for (const QString &user : getClientList()) {
        if (userMap[user]->isReady()) {
            userMap[user]->toggleReady();
        }
    }

    emit readyListChanged(getReadyUsersStr(), getClientList());
}

bool Lobby::containsNickname(QString nickname) {
    QMap<QString, User*>::iterator it = userMap.begin();
    for (; it != userMap.end(); it++) {
        if (it.value()->getNickname() == nickname) {
            return true;
        }
    }
    return false;
}


// Returns a QStringList containing all the usersIDs
QStringList Lobby::getClientList() { return userMap.keys(); }

QString Lobby::getUserNick(QString clientID) { return userMap[clientID]->getNickname(); }

// Returns a QString containing the user nicknames. Ex.: hadson0,whoamI,user_1
QString Lobby::getUsersToStr() {
    QString userNicks;

    QMap<QString, User *>::iterator it = userMap.begin();
    for (; it != userMap.end(); it++) {
        userNicks.append(it.value()->getNickname() + ",");
    }
    userNicks.chop(1);

    return userNicks;
}

QString Lobby::getReadyUsersStr() {
    QString readyUserList;

    QMap<QString, User *>::iterator it = userMap.begin();
    for (; it != userMap.end(); it++) {
        if (it.value()->isReady()) { // If the user is ready
            readyUserList.append(it.value()->getNickname() + ",");
        }
    }
    readyUserList.chop(1);

    return readyUserList;
}

void Lobby::toggleReady(QString clientID) {
    if (userMap.contains(clientID)) {
        userMap[clientID]->toggleReady();

        emit readyListChanged(getReadyUsersStr(), getClientList());
    }
}

