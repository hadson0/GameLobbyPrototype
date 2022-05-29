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
    QString getUserNicksStr();
    QString getReadyUsersStr();

    // Setters
    void setReady(QString clientID, bool ready);

    //Methods
    void addUser(QString clientID, QString nickname);
    void removeUser(QString clientID);
    bool containsNickname(QString nickname);

signals:
    void userReadyChanged();
};

#endif // LOBBY_H
