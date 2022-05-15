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
    //qDebug() << "Server App: Message to process: " << message;

    static QRegularExpression separator(",");

    QString type = getMessageData(message, "type");
    QString lobbyID = "", senderID = "", payLoad = "";

    //type:createGame;payLoad:0000;senderID:1234
    if (type == "createGame") {
        qDebug() << "Create game request";

        senderID = getMessageData(message, "senderID");
        if (!senderID.isEmpty()) {
            emit createLobbyRequest(senderID);
        }
    }

    //type:joinGame;payLoad:1234;sender:5678
    else if (type == "joinGame") {
        qDebug() << "Join game request";

        lobbyID = getMessageData(message, "payLoad");
        senderID = getMessageData(message, "senderID");

        if (!lobbyID.isEmpty() && !senderID.isEmpty()) {
            emit joinLobbyRequest(lobbyID, senderID);
        }
    }

    //type:message;payLoad:HelloLobby;lobbyID:1234senderID:5678
    else if (type == "message") {
        qDebug() << "Lobby message request";

        payLoad = getMessageData(message, "payLoad");
        lobbyID = getMessageData(message, "lobbyID");
        senderID = getMessageData(message, "senderID");

        if (!payLoad.isEmpty() && !lobbyID.isEmpty() && !senderID.isEmpty()) {
            emit messageLobbyRequest(payLoad, lobbyID, senderID);
        }
    }
}
