#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "Controllers/messageprocesshandler.h"

class GameManager : public QObject {
    Q_OBJECT

    QString clientID; // Lobby host ID (who created the lobby)
    QString lobbyID, nickname;

    MessageProcessHandler *messageProcessHandler;

    static GameManager *instance;
    GameManager(QObject *parent = nullptr);

public:
    GameManager(const GameManager &obj) = delete;
    GameManager(const GameManager &&obj) = delete;
    GameManager operator=(GameManager &obj) = delete;
    GameManager operator=(GameManager &&obj) = delete;

    static GameManager *getInstance(QObject *parent = nullptr) {
        if (instance == nullptr) {
            instance = new GameManager(parent);
        }

        return instance;
    }

    // Getters
    QString getLobbyID();

public slots:    
    // Setters
    void setClientID(QString clientID);
    void setLobbyID(QString lobbyID);

    // Methods   
    void toggleReadyRequest();
    void createLobbyRequest(QString nickname);
    void joinLobbyRequested(QString lobbyID, QString nickname);
    void quitLobbyRequest();
    void sendLobbyMessageRequested(QString message);
    void onLobbyJoined(QString lobbyID, QStringList userList);
    void leaveLobby();

signals:
    void processSocketMessage(QString message);
    void processScreenMessage(QString message);

    void connectToServerRequest();
    void clientConnected();
    void userListChanged(QStringList newUserList);
    void readyListChanged(QStringList readyUsers);
    void lobbyIDChanged(QString newLobbyID);
    void lobbyLeft();

    void newLobbyMessageRecieved(QString message, QString senderNick);
    void newMessageReadyToSend(QString message);
    void joinedLobby();

    void error(QString error);
};

#endif // GAMEMANAGER_H
