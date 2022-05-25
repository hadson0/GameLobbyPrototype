#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <random>
#include <QDebug>

#include "websockethandler.h"
#include "messageprocesshandler.h"
#include "lobby.h"

class GameManager : public QObject {
    Q_OBJECT

    QMap<QString, Lobby*> lobbyMap;

    WebSocketHandler *webSocketHandler;
    MessageProcessHandler *messageProcessorHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    QString generateRandomID();

public slots:
    void createLobbyRequest(QString clientID, QString nickname);
    void joinLobbyRequest(QString lobbyID, QString clientID, QString nickname);
    void quitLobbyRequest(QString lobbyID, QString clientID);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);
    void setReadyRequest(QString lobbyID, QString clintID, bool ready);
    void onClientReadyChanged();
};

#endif // GAMEMANAGER_H
