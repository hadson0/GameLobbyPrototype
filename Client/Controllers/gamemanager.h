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
    void setClientID(QString clientID);
    void setLobbyID(QString lobbyID);
    void setClientList(QStringList clients);
    void setReadyList(QStringList readyClients);

    // Methods   
    void toggleReadyRequest();
    void createLobbyRequest(QString nickname);
    void joinLobbyRequested(QString lobbyID, QString nickname);
    void quitLobbyRequest();
    void sendLobbyMessageRequested(QString message);
    void onLobbyJoined(QString lobbyID, QStringList clients);

signals:
    void processSocketMessage(QString message);
    void processScreenMessage(QString message);

    void connectToServerRequest();
    void clientConnected();
    void clientListChanged(QStringList clientList);
    void readyListChanged(QStringList readyClients);
    void lobbyIDChanged(QString newLobbyID);
    void lobbyLeft();

    void newLobbyMessageRecieved(QString message);
    void newMessageReadyToSend(QString message);
    void inGameLobby();

    void error(QString error);
};

#endif // GAMEMANAGER_H
