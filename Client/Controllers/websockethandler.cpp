#include "websockethandler.h"

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent} {
    webSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);

    // Connects signals and slots
    connect(webSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(webSocket, &QWebSocket::textFrameReceived, this, &WebSocketHandler::onTextMessageReceived);
}

WebSocketHandler::~WebSocketHandler() {
    webSocket->close();
}

void WebSocketHandler::connectToServer(QString hostAddress) {
    qDebug() << "Client App: Connect to server: " << hostAddress;
    webSocket->open(hostAddress);
}

void WebSocketHandler::sendMessageToServer(QString message) {
    webSocket->sendTextMessage(message);
}

void WebSocketHandler::onConnected() {}

void WebSocketHandler::onTextMessageReceived(QString message) {
    emit newMessageReadyForProcessing(message);
    //qDebug() << "Message recieved: " << message;
}
