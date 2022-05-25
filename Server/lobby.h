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


    // Getters
    QStringList getClientList();
    QString getClientListToStr();
    QStringList getReadyClientsList();
    QString getReadyListToStr();

    // Setters
    void setReady(QString clientID, bool ready);

    //Methods
    void addClient(QString clientID);
    void removeClient(QString clientID);

signals:
    void clientReadyChanged();
};

#endif // LOBBYHANDLER_H
