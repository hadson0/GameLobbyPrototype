#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <random>
#include <QDebug>

#include "websockethandler.h"
#include "messageprocesshandler.h"
#include "lobbyhandler.h"

class GameManager : public QObject {
    Q_OBJECT

    QMap<QString, LobbyHandler*> lobbyMap;

    WebSocketHandler *webSocketHandler;
    MessageProcessHandler *messageProcessorHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    QString generateRandomID();

public slots:
    void createLobbyRequest(QString clientID);
    void joinLobbyRequest(QString lobbyID, QString clientID);
    void quitLobbyRequest(QString lobbyID, QString clientID);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);
    void setReadyRequest(QString lobbyID, QString clintID, bool ready);
    void onClientReadyChanged();
};

#endif // GAMEMANAGER_H
