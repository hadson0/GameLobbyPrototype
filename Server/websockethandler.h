#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <random>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

class WebSocketHandler : public QObject {
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

    QString generateRandomID();
    void sendTextMessage(QString message, QString clientID);
    void sendTextMessageToClients(QString message, QStringList clientsID);

public slots:
    void onNewSocketConnection();
    void onTextMessageReceived(QString message);
    void onSocketDisconnected();

signals:
    void newMessageToProcess(QString message);

private:
    QWebSocketServer *webSocketServer;
    QMap<QString, QWebSocket *> clientMap; // Map of all the registered clients (WebSockets) on the server
};

#endif // WEBSOCKETHANDLER_H
