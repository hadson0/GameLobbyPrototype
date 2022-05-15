#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "Controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT

    QString clientID; // Lobby host ID (who created the lobby)
    QMap<QString, bool> clientMap; // <ClientID, isReady>
    QString lobbyID;

    MessageProcessHandler *messageProcessHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    // Getters
    QString getLobbyID();
    QStringList getClientList();

public slots:    
    // Setters
    void setLobbyID(QString lobbyID);
    void setClientList(QStringList clients);

    // Methods
    void createLobbyRequest();
    void joinLobbyRequested(QString lobbyID);
    void sendLobbyMessageRequested(QString message);
    void onLobbyJoined(QString lobbyID, QStringList clients);
    void registerClientID(QString clientID);

signals:
    void processSocketMessage(QString message);
    void processScreenMessage(QString message);

    void clientListChanged(QStringList clientList);
    void lobbyIDChanged(QString newLobbyID);
    void lobbyLeft();

    void newLobbyMessageRecieved(QString message);
    void newMessageReadyToSend(QString message);
    void inGameLobby();
};

#endif // GAMEMANAGER_H
