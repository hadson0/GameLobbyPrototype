#ifndef LOBBYHANDLER_H
#define LOBBYHANDLER_H

#include <QObject>
#include <QMap>

class LobbyHandler : public QObject {
    Q_OBJECT

    QString lobbyID;
    QMap<QString, bool> clientMap; // <ClientID, isReady>

public:
    explicit LobbyHandler(QString lobbyID, QObject *parent);

    void addClient(QString clientID);

    // Getters
    QStringList getClientList();
    QString getClientListToStr();
    QStringList getReadyClientsList();
    QString getReadyListToStr();

    //Methods
    void setReady(QString clientID, bool ready);

signals:
    void clientReadyChanged();
};

#endif // LOBBYHANDLER_H
