#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>

class GameLobbyHandler : public QObject
{
    Q_OBJECT
public:
    explicit GameLobbyHandler(QString lobbyID, QObject *parent);

    void addClient(QString clientID);
    QString getClientListToString();
    QStringList getClientList();

signals:

private:
    QString lobbyID;
    QStringList clientList;
};

#endif // GAMELOBBYHANDLER_H
