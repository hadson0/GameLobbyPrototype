#include "websockethandler.h"

WebSocketHandler *WebSocketHandler::instance = nullptr;

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent} {
    webSocket = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);



    // Connects signals and slots
    connect(webSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(webSocket, &QWebSocket::textFrameReceived, this, &WebSocketHandler::onTextMessageReceived);
    connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this,
            [this](const QAbstractSocket::SocketError error) {
                Q_UNUSED(error);
                emit connectionError();
            });
}

WebSocketHandler::~WebSocketHandler() {
    webSocket->close();
}

bool WebSocketHandler::isValid() {
    return webSocket->isValid();
}

void WebSocketHandler::connectToServer(QString hostAddress) {
    webSocket->open(hostAddress);
}

void WebSocketHandler::sendMessageToServer(QString message) {
    webSocket->sendTextMessage(message);
}

void WebSocketHandler::close() {
    webSocket->close();
}

void WebSocketHandler::onConnected() {}

void WebSocketHandler::onTextMessageReceived(QString message) {
    emit newMessageReadyForProcessing(message);
    //qDebug() << "Message recieved: " << message;
}
