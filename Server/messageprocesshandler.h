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
    void processMessage(QString message);

signals:
    void createLobbyRequest(QString clientID);
    void joinLobbyRequest(QString lobbyID, QString uniqueID);
    void messageLobbyRequest(QString message, QString lobbyID, QString senderID);
};

#endif // MESSAGEPROCESSHANDLER_H
