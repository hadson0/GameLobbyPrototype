#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QDebug>
#include <QtWebSockets/QWebSocket>

class WebSocketHandler : public QObject {
    Q_OBJECT

    QWebSocket *webSocket;

    static WebSocketHandler *instance;
    WebSocketHandler(QObject *parent = nullptr);

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

    bool isValid();
    void connectToServer(QString hostAddress);
    void sendMessageToServer(QString message);
    void close();

public slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void newMessageReadyForProcessing(QString message);   
    void connectionError();
};

#endif // WEBSOCKETHANDLER_H
