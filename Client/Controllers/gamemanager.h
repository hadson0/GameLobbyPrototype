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


public slots:
    void onCreateLobbyRequested();
    void onJoinLobbyRequested(QString lobbyID);
    void onSendLobbyMessageRequested(QString message);

    void setLobbyID(QString lobbyID);
    void setClientList(QStringList clients);

    void registerUniqueID(QString uniqueID);

    void onLobbyJoined(QString lobbyID, QStringList clients);

signals:
    void processSocketMessage(QString message);
    void processScreenMessage(QString message);

    void lobbyIDChanged(QString newLobbyID);
    void lobbyLeft();
    void clientsInLobbyChanged();

    void inGameLobby();
    void newMessageReadyToSend(QString message);
    void newLobbyMessageRecieved(QString message);
};

#endif // GAMEMANAGER_H
