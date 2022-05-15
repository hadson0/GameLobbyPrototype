#ifndef MESSAGEPROCESSHANDLER_H
#define MESSAGEPROCESSHANDLER_H

#include <QObject>
#include <QDebug>
#include <QRegularExpression>

class MessageProcessHandler : public QObject {
    Q_OBJECT

public:
    explicit MessageProcessHandler(QObject *parent = nullptr);

public slots:
    void processSocketMessage(QString message);

signals:
    void createLobbyRequest(QString clientID);
    void joinLobbyRequest(QString lobbyID, QString clientID);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);
    void setReadyRequest(QString lobbyID, QString clientID, bool ready);
};

#endif // MESSAGEPROCESSHANDLER_H
