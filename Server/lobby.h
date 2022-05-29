#ifndef LOBBY_H
#define LOBBY_H

#include <QObject>
#include <QMap>
#include <QDebug>

#include "user.h"

class Lobby : public QObject {
    Q_OBJECT

    QString lobbyID;
    QMap<QString, User *> userMap; // <clientID, User>

public:
    explicit Lobby(QString lobbyID, QObject *parent);

    // Getters
    QStringList getClientList();
    QString getUserNick(QString clientID);
    QString getUsersToStr();
    QString getReadyUsersStr();

    // Setters
    void toggleReady(QString clientID);

    //Methods
    void addUser(QString clientID, QString nickname);
    void removeUser(QString clientID);
    bool containsNickname(QString nickname);

signals:
    void readyListChanged(QString readyUsers, QStringList clientList);
};

#endif // LOBBY_H
