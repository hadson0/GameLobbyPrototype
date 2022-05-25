#include "messageprocesshandler.h"

MessageProcessHandler::MessageProcessHandler(QObject *parent)
    : QObject{parent} {}

// Extracts the data from the message and returns it
QString getMessageData(QString message, QString dataIdentifier) {
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
    QString type = getMessageData(message, "type");
    QString lobbyID = "", senderID = "", payLoad = "", nickname = "";

    //type:createGame;payLoad:0000;senderID:1234;nickname:hadson0
    if (type == "createGame") {
        senderID = getMessageData(message, "senderID");
        nickname = getMessageData(message, "nickname");

        if (!senderID.isEmpty()) {
            qDebug() << "Create game request, client ID: " << senderID;
            emit createLobbyRequest(senderID, nickname);
        }
    }

    //type:joinGame;payLoad:1234;sender:5678;nickname:hadson0
    else if (type == "joinGame") {

        lobbyID = getMessageData(message, "payLoad");
        senderID = getMessageData(message, "senderID");
        nickname = getMessageData(message, "nickname");

        if (!lobbyID.isEmpty() && !senderID.isEmpty()) {
            qDebug() << "Join game request, client ID: " << senderID;
            emit joinLobbyRequest(lobbyID, senderID, nickname);
        }
    }

    //type:message;payLoad:HelloLobby;lobbyID:1234;senderID:5678
    else if (type == "message") {

        payLoad = getMessageData(message, "payLoad");
        lobbyID = getMessageData(message, "lobbyID");
        senderID = getMessageData(message, "senderID");

        if (!payLoad.isEmpty() && !lobbyID.isEmpty() && !senderID.isEmpty()) {
            qDebug() << "Lobby message request, client ID: " << senderID;
            emit messageLobbyRequest(payLoad, lobbyID, senderID);
        }
    }

    // type:setReady;payLoad:1;lobbyID:5678;senderID:1234
    else if (type == "setReady") {

        payLoad = getMessageData(message, "payLoad");
        lobbyID = getMessageData(message, "lobbyID");
        senderID = getMessageData(message, "senderID");

        if (!payLoad.isEmpty() && !lobbyID.isEmpty() && !senderID.isEmpty()) {
            qDebug() << "Set ready request, client ID: " << senderID;
            emit setReadyRequest(lobbyID, senderID, payLoad.toInt());
        }
    }

    // type:quitLobbyRequest;payLoad:0;lobbyID:1234;senderID:5678
    else if (type == "quitLobbyRequest") {

        lobbyID = getMessageData(message, "lobbyID");
        senderID = getMessageData(message, "senderID");

        if (!lobbyID.isEmpty() && !senderID.isEmpty()) {
            qDebug() << "Client left the lobby, ID: " << senderID;
            emit quitLobbyRequest(lobbyID, senderID);
        }
    }
}
