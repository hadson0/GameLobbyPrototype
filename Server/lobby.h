#ifndef LOBBY_H
#define LOBBY_H

#include <QObject>
#include <QMap>

#include "user.h"

class Lobby : public QObject {
    Q_OBJECT

    QString lobbyID;
    QMap<QString, User *> clientMap; // <ClientID, User>

public:
    explicit Lobby(QString lobbyID, QObject *parent);

    // Getters
    QStringList getClientList();
    QString getClientsInfo();
    QStringList getReadyClientIDList();
    QString getReadyListToStr();

    // Setters
    void setReady(QString clientID, bool ready);

    //Methods
    void addClient(QString clientID, QString nickname);
    void removeClient(QString clientID);

signals:
    void clientReadyChanged();
};

#endif // LOBBY_H
