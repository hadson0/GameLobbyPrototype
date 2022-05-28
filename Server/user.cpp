#include "user.h"

User::User(QString nickname, QObject *parent)
    : QObject{parent}, nickname(nickname) {}

bool User::isReady() { return ready; }

QString User::getNickname() { return nickname; }

void User::setReady(bool ready) { this->ready = ready; }

void User::setNickname(QString nickName) { this->nickname = nickName; }
