#ifndef MESSAGEPROCESSHANDLER_H
#define MESSAGEPROCESSHANDLER_H

#include <QObject>
#include <QRegularExpression>
#include <QDebug>

class MessageProcessHandler : public QObject {
    Q_OBJECT
public:
    explicit MessageProcessHandler(QObject *parent = nullptr);

    QString getMessageData(QString message, QString dataIdentifier);

public slots:
    void processSocketMessage(QString message);
    void processScreenMessage(QString message);

signals:
    // Socket related signals
    void clientIDRegistration(QString clientID);
    void newLobby(QString newLobbyID, QStringList newClientList);
    void lobbyListUpdated(QStringList newClientList);
    void newLobbyMessageRecieved(QString message);

    // Screen related signals
    void createLobbyRequest();
    void joinLobbyRequest(QString newLobbyID);
    void sendLobbyMessageRequest(QString message);
    void displayScreenRequest(QString destinationScreen);
};

#endif // MESSAGEPROCESSHANDLER_H
