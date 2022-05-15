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

    QWebSocketServer *webSocketServer;
    QMap<QString, QWebSocket *> clientMap;

public:
    explicit WebSocketHandler(QObject *parent = nullptr);

    QString generateRandomID();
    void sendTextMessage(QString message, QString clientID);
    void sendTextMessageToClients(QString message, QStringList clientsID);

public slots:
    void onNewSocketConnection();
    void onTextMessageReceived(QString message);
    void onSocketDisconnected();

signals:
    void newMessageToProcess(QString message);    
};

#endif // WEBSOCKETHANDLER_H
