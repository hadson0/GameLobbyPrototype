#include "websockethandler.h"

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent} {
    webSocket = new QWebSocket();

    // Connects signals and slots
    connect(webSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(webSocket, &QWebSocket::textFrameReceived, this, &WebSocketHandler::onTextMessageReceived);
}

WebSocketHandler::~WebSocketHandler() {
    // Guarantees that memory will be deallocated
    webSocket->deleteLater();
}

void WebSocketHandler::connectToServer(QString hostAddress) {
    qDebug() << "Client App: Connect to server: " << hostAddress;
    webSocket->open(hostAddress);
}

void WebSocketHandler::sendMessageToServer(QString message) {
    webSocket->sendTextMessage(message);
}

void WebSocketHandler::onConnected() {
    qDebug() << "Client App: New client connected!";
}

void WebSocketHandler::onTextMessageReceived(QString message) {
    qDebug() << "Client App: Received message: " << message;
    emit newMessageReadyForProcessing(message);
}
