#include "websockethandler.h"

WebSocketHandler *WebSocketHandler::instance = nullptr;

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent} {
    webSocketServer = new QWebSocketServer("GamePrototypeServer",  QWebSocketServer::NonSecureMode, this);

    // Connects signals and slots
    connect(webSocketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewSocketConnection);

    // Checks if the server is running properly
    if (webSocketServer->listen(QHostAddress::Any, 8585)) {
        qDebug() << "Server is running";
    } else {
        qDebug() << "Error starting to listen for new connections";
    }
}

WebSocketHandler::~WebSocketHandler() {
    webSocketServer->close();
}

// Generates a QString composed of 4 random numbers. Ex.: "1234"
QString WebSocketHandler::generateRandomID() {
    std::random_device rd;
    std:: default_random_engine generator(rd());
    std::uniform_int_distribution<int> idGenerator(1000, 9999);
    return QString::number(idGenerator(generator));
}

// Sends a text message to a client
void WebSocketHandler::sendTextMessage(QString message, QString clientID) {
    // Checks if the client is registered
    if (clientMap.contains(clientID)) {
        QWebSocket *client = clientMap[clientID];
        client->sendTextMessage(message);
         qDebug() << "Send message:" << message;
    }
}

// Sends a text message to multiple clients
void WebSocketHandler::sendTextMessage(QString message, QStringList clientsID) {
    for (auto &clientID : clientsID)
        sendTextMessage(message, clientID);
}

void WebSocketHandler::onNewSocketConnection() {
    QString newClientID = generateRandomID();

    // Make surte that the generated ID is unique
    QStringList existingKeys = clientMap.keys();
    for (; existingKeys.contains(newClientID); newClientID = generateRandomID());

    // Returns the next pending connection as a connected QWebSocket object
    QWebSocket *newClient  = webSocketServer->nextPendingConnection();

    //Connects signals and slots of the new client
    connect(newClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageReceived);
    connect(newClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnected);

    // Sends the client unique ID to the client
    newClient->sendTextMessage("type:uniqueID;payLoad:" + newClientID);

    // Registers the new client
    clientMap[newClientID] = newClient;

    qDebug() << "New client connected, ID:" << newClientID;
}

void WebSocketHandler::onTextMessageReceived(QString message) {
     qDebug() << "Server received: " << message;
    emit newMessageToProcess(message);
}

void WebSocketHandler::onSocketDisconnected() {
    // Gets the client that sent the signal using the sender function
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());

    try {
        // Iterates through the map until it finds the client, then disconnect it (delete it)
        for (auto it = clientMap.begin(); it != clientMap.end(); it++) {
            if (it.value()->peerAddress() == client->peerAddress() && it.value()->peerPort() == client->peerPort()) {
                QString clientID = it.key();
                clientMap.remove(clientID);
                client->deleteLater();

                qDebug() << "Client disconnected, ID: " << clientID;
                emit clientDisconnected(clientID);
                break;
            }
        }
    } catch (...) {
        qDebug() << "Error disconnecting client";
    }
}
