#include "messageprocesshandler.h"

MessageProcessHandler::MessageProcessHandler(QObject *parent)
    : QObject{parent} {}

// Extracts the data from the message and returns it
QString MessageProcessHandler::getMessageData(QString message, QString dataIdentifier) {
    QRegularExpression separator;
    separator.setPattern(";");

    // Searches for the data and returns it;
    for (QString &message : message.split(separator)) {
        if (message.contains(dataIdentifier)) {
            return message.remove(dataIdentifier + ":");
        }
    }

    // If the data isn't in the message, returns an empty QString
    return "";
}

void MessageProcessHandler::processSocketMessage(QString message) {
    // qDebug() << "Client App: Message to process: " << message;

    static QRegularExpression separator(",");

    QString type = getMessageData(message, "type");
    QString clientID = "", lobbyID = "", senderID = "", lobbyMessage = "";
    QStringList clientList;

    // type:uniqueId;payLoad:1234
    if (type == "uniqueID") {

        clientID = getMessageData(message, "payLoad");
        if (!clientID.isEmpty()) {
            qDebug() << "Client ID received: " << clientID;
            emit setClientID(clientID);
        }
    }

    // type:newLobbyCreated;payLoad:1234;clientList:hadson0:4312
    else if (type == "newLobbyCreated" || type == "joinSuccess") {
        lobbyID = getMessageData(message, "payLoad");
        QString clientListString = getMessageData(message, "clientList");
        clientList = clientListString.split(separator);


        if (!lobbyID.isEmpty() && !clientList.isEmpty()) {
            qDebug() << "New lobby, ID: " << lobbyID;
            emit newLobby(lobbyID, clientList);
        }
    }

    // type:updatedClientList;payLoad:1234,5678,4444
    else if (type == "updatedClientList") {
        clientList = getMessageData(message, "clientList").split(separator);

        if (!clientList.isEmpty()) {
            qDebug() << "Clients in lobby: " << clientList;
            emit clientListUpdated(clientList);
        }
    }

    // type:lobbyMessage;payLoad:HelloWorld;senderID:1234
    else if (type == "lobbyMessage") {

        lobbyMessage = getMessageData(message, "payLoad");
        senderID = getMessageData(message, "senderID");

        if (!lobbyMessage.isEmpty() && !senderID.isEmpty()) {
            QString displayMessage = senderID + ": " + lobbyMessage;

            emit newLobbyMessageRecieved(displayMessage);
        }
    }

    // type:updatedReadyClientList;payLoad:0;clientList:3090
    else if (type == "updatedReadyClientList") {
        clientList = getMessageData(message, "clientList").split(separator);

        if (!clientList.isEmpty()) {
            qDebug() << "Ready clients in lobby: " << clientList;
            emit readyListUpdated(clientList);
        }
    }

    // Errors

    // type:joinError;payLoad:DNE
    else if (type == "joinError" || type == "quitError" || type == "lobbyMessageError") {
        emit error(type);
    }
}

void MessageProcessHandler::processScreenMessage(QString message) {
    QString type = getMessageData(message, "type");
    QString nickname = "", newLobbyID = "", lobbyMessage = "";

    // type:connectToServerRequest;payLoad:0
    if (type == "connectToServerRequest") {
            emit connectToServerRequest();

    }

    // type:createLobbyRequest;payload:0;nickname:hadson0
    if (type == "createLobbyRequest") {
        nickname = getMessageData(message, "nickname");

        if (!nickname.isEmpty()) {
            emit createLobbyRequest(nickname);
        }
    }

    // type:joinLobbyRequest;payLoad:1234
    else if (type == "joinLobbyRequest") {
        newLobbyID = getMessageData(message, "payLoad");
        nickname = getMessageData(message, "nickname");

        if (!newLobbyID.isEmpty() && !nickname.isEmpty()) {
            emit joinLobbyRequest(newLobbyID, nickname);
        }
    }

    // type:sendLobbyMessageRequest;payload:" + message
    else if (type == "sendLobbyMessageRequest") {
        lobbyMessage = getMessageData(message, "payLoad");
        if (!lobbyMessage.isEmpty()) {
            emit sendLobbyMessageRequest(lobbyMessage);
        }
    }

    // type:toggleReadyRequest;payLoad:0
    else if (type == "toggleReadyRequest") {
        emit toggleReadyRequest();
    }

    // type:quitLobbyRequest;payLoad:0;
    else if (type == "quitLobbyRequest") {
        emit quitLobbyRequest();
    }
}
