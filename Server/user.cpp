#include "user.h"

User::User(QString clientID, QString nickname, QObject *parent)
    : QObject{parent}, clientID(clientID), nickname(nickname) {}

bool User::isReady() { return ready; }

QString User::getNickname() { return nickname; }

QString User::getClientID() { return clientID; }

void User::setReady(bool ready) { this->ready = ready; }

void User::setClientID(QString clientID) { this->clientID = clientID; }

void User::setNickname(QString nickName) { this->nickname = nickName; }
