#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QDebug>
#include <QtWebSockets/QWebSocket>

class WebSocketHandler : public QObject {
    Q_OBJECT
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

    void connectToServer(QString hostAddress);
    void sendMessageToServer(QString message);

public slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void newMessageReadyForProcessing(QString message);

private:
    QWebSocket *webSocket;
};

#endif // WEBSOCKETHANDLER_H
