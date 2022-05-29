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
    // qDebug() << "User App: Message to process: " << message;

    static QRegularExpression separator(",");

    QString type = getMessageData(message, "type");
    QString clientID = "", lobbyID = "", senderNick = "", lobbyMessage = "", errorCode = "";
    QStringList userList;

    // type:uniqueId;payLoad:1234
    if (type == "uniqueID") {

        clientID = getMessageData(message, "payLoad");
        if (!clientID.isEmpty()) {
            qDebug() << "User ID received: " << clientID;
            emit setClientID(clientID);
        }
    }

    // type:newLobbyCreated;payLoad:"1234;userList:hadson0,whoam1
    else if (type == "newLobbyCreated" || type == "joinSuccess") {
        lobbyID = getMessageData(message, "payLoad");
        userList = getMessageData(message, "userList").split(separator);

        if (!lobbyID.isEmpty() && !userList.isEmpty()) {
            qDebug() << "New lobby, ID: " << lobbyID;
            emit newLobby(lobbyID, userList);
        }
    }

    // type:updatedUserList;payLoad:0;userList:hadson0,whoam1
    else if (type == "updatedUserList") {
        userList = getMessageData(message, "userList").split(separator);

        if (!userList.isEmpty()) {
            qDebug() << "Users in lobby: " << userList;
            emit userListUpdated(userList);
        }
    }

    // type:lobbyMessage;payLoad:HelloLobby;senderNick:hadson0
    else if (type == "lobbyMessage") {
        lobbyMessage = getMessageData(message, "payLoad");
        senderNick = getMessageData(message, "senderNick");

        if (!lobbyMessage.isEmpty() && !senderNick.isEmpty()) {
            emit newLobbyMessageRecieved(lobbyMessage, senderNick);
        }
    }

    // type:updatedReadyUserList;payLoad:0;userList:hadson0,whoam1
    else if (type == "updatedReadyUserList") {
        userList = getMessageData(message, "userList").split(separator);

        if (!userList.isEmpty()) {
            qDebug() << "Ready users in lobby: " << userList;
            emit readyListUpdated(userList);
        }
    }

    // Errors

    // type:joinError;payLoad:DNE
    else if (type == "error") {
        errorCode = getMessageData(message, "payLoad");
        if (!errorCode.isEmpty()) {            
            emit error(errorCode);
        }
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

    // type:sendLobbyMessageRequest;payload:HelloLobby
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
