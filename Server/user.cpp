#include "user.h"

User::User(QString nickname, QObject *parent)
    : QObject{parent}, nickname(nickname), ready(false) {}

bool User::isReady() { return ready; }

QString User::getNickname() { return nickname; }

void User::toggleReady() { ready = !ready; }

void User::setNickname(QString nickName) { this->nickname = nickName; }
