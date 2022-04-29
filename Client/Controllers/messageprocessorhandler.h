#ifndef MESSAGEPROCESSORHANDLER_H
#define MESSAGEPROCESSORHANDLER_H

#include <QObject>
#include <QRegularExpression>
#include <QDebug>

class MessageProcessHandler : public QObject {
    Q_OBJECT
public:
    explicit MessageProcessHandler(QObject *parent = nullptr);

    void processMessage(QString message);
    QString getMessageData(QStringList messageSeparated, QString dataIdentifier);

signals:
    void uniqueIDRegistration(QString uniqueID);
    void newLobby(QString lobbyID, QStringList clientList);
    void lobbyListUpdated(QStringList clientList);
    void newLobbyMessage(QString message);
};

#endif // MESSAGEPROCESSORHANDLER_H
