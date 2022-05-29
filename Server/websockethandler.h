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

    WebSocketHandler(QObject *parent = nullptr);
    static WebSocketHandler *instance;

public:
    WebSocketHandler(const WebSocketHandler &obj) = delete;
    WebSocketHandler(const WebSocketHandler &&obj) = delete;
    WebSocketHandler operator=(WebSocketHandler &obj) = delete;
    WebSocketHandler operator=(WebSocketHandler &&obj) = delete;
    ~WebSocketHandler();

    static WebSocketHandler *getInstance(QObject *parent = nullptr) {
        if (instance == nullptr) {
            instance = new WebSocketHandler(parent);
        }

        return instance;
    }

    QString generateRandomID();
    void sendTextMessage(QString message, QString clientID);
    void sendTextMessage(QString message, QStringList clientIDList);

public slots:
    void onNewSocketConnection();
    void onTextMessageReceived(QString message);
    void onSocketDisconnected();

signals:
    void newMessageToProcess(QString message);
    void clientDisconnected(QString clientID);
};

#endif // WEBSOCKETHANDLER_H
