#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>
#include <QMap>

class GameLobbyHandler : public QObject {
    Q_OBJECT

    QString lobbyID;
    QMap<QString, bool> clientMap; // <ClientID, isReady>

    void toggleReady(QString clientID);

public:
    explicit GameLobbyHandler(QString lobbyID, QObject *parent);

    void addClient(QString clientID);

    // Getters
    QStringList getClientList();
    QString getClientListToStr();
    QStringList getReadyClientsList();
    QString getReadyClientsListToStr();

signals:
    void clientReadyChanged();
};

#endif // GAMELOBBYHANDLER_H
