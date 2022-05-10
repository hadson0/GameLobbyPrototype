#include "messageprocesshandler.h"

MessageProcessHandler::MessageProcessHandler(QObject *parent)
    : QObject{parent} {}

// Extracts the data from the message and returns it
QString MessageProcessHandler::getMessageData(QString message, QString dataIdentifier) {
    // Separates the message
    QRegularExpression separator;
    separator.setPattern(";");

    // Searches for the data and returns it;
    for (QString &message : message.split(separator)) {
        if (message.contains(dataIdentifier))
            return message.remove(dataIdentifier + ":");
    }

    // If the data isn't in the message, returns an empty QString
    return QString();
}

void MessageProcessHandler::processSocketMessage(QString message) {
    // qDebug() << "Client App: Message to process: " << message;

    static QRegularExpression separator(",");

    QString type = getMessageData(message, "type");
    QString clientID = QString(), lobbyID = QString(), senderID = QString(), lobbyMessage = QString();
    QStringList clientList = QStringList();

    // type:uniqueId;payLoad:1234
    if (type == "uniqueID") {

        clientID = getMessageData(message, "payLoad");
        if (!clientID.isEmpty()) {
            qDebug() << "Client App: unique ID received " << clientID;
            emit uniqueIDRegistration(clientID);
        }
    }

    // type:newLobbyCreated;payLoad:1234;clientList:4312,856,5678
    else if (type == "newLobbyCreated" || type == "joinSuccess") {
        lobbyID = getMessageData(message, "payLoad");
        QString clientListString = getMessageData(message, "clientList");
        clientList = clientListString.split(separator);

        qDebug() << "Client App: Clients in lobby: " << clientListString;

        if (!lobbyID.isEmpty() && !clientList.isEmpty())
            emit newLobby(lobbyID, clientList);
    }

    // type:updatedClientList;payLoad:1234,5678,4444
    else if (type == "updatedClientList") {
        qDebug() << "Client App: Received updated client list";

        clientList = getMessageData(message, "payLoad").split(separator);

        if (!clientList.isEmpty())
            emit lobbyListUpdated(clientList);
    }

    // type:lobbyMessage;payLoad:HelloWorld;senderID:1234
    else if (type == "lobbyMessage") {

        lobbyMessage = getMessageData(message, "payLoad");
        senderID = getMessageData(message, "senderID");

        if (!lobbyMessage.isEmpty() && !senderID.isEmpty()) {
            QString displayMessage = senderID + ": " + lobbyMessage;

            qDebug() << "Client App: New lobby message received";
            emit newLobbyMessageRecieved(displayMessage);
        }
    }
}

void MessageProcessHandler::processScreenMessage(QString message) {
    QString type = getMessageData(message, "type");
    QString newLobbyID = QString(), lobbyMessage = QString();

    // type:createLobbyRequest;payload:0`
    if (type == "createLobbyRequest") {
        emit createLobbyRequest();
    }

    // type:joinLobbyRequest;payLoad:1234
    else if (type == "joinLobbyRequest") {
        newLobbyID = getMessageData(message, "payLoad");
        if (!newLobbyID.isEmpty())
            emit joinLobbyRequest(newLobbyID);
    }

    // type:sendLobbyMessageRequest;payload:" + message
    else if (type == "sendLobbyMessageRequest") {
        lobbyMessage = getMessageData(message, "payLoad");
        if (!lobbyMessage.isEmpty())
            emit sendLobbyMessageRequest(lobbyMessage);
    }
}
