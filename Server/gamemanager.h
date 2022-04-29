#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <random>
#include "websockethandler.h"
#include "messageprocesshandler.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    QString generateRandomID();

public slots:
    void createLobbyRequest(QString clientID);
    void joinLobbyRequest(QString lobbyId, QString clientID);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);

signals:

private:
    QString lobbyID;
    QMap<QString, GameLobbyHandler*> lobbyMap;

    WebSocketHandler *webSocketHandler;
    MessageProcessHandler *messageProcessorHandler;
};

#endif // GAMEMANAGER_H
