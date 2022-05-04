#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "Controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT

    QString clientID; // Lobby host ID (who created the lobby)
    QStringList clientList; // List of the clients in the lobby
    QString lobbyID;

    MessageProcessHandler *messageProcessHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    QString getLobbyID();
    QStringList getClientsInLobby();

    void createGameRequest();
    void joinLobbyRequest(QString lobbyID);    

public slots:
    void sendMessageToLobby(QString message);

    void setLobbyID(QString lobbyID);
    void setClientList(QStringList clients);

    void processSocketMessage(QString message);
    void registerUniqueID(QString uniqueID);

    void onLobbyJoined(QString lobbyID, QStringList clients);

signals:
    void lobbyIDChanged(QString newLobbyID);
    void clientsInLobbyChanged();

    void newMessageReadyToSend(QString message);
    void inGameLobby();
    void newLobbyMessage(QString message);
};

#endif // GAMEMANAGER_H
