#include "messageprocesshandler.h"

MessageProcessHandler::MessageProcessHandler(QObject *parent)
    : QObject{parent} {}

// Extracts the data from the message and returns it
QString getMessageData(QStringList messageSeparated, QString dataIdentifier) {
    for(QString &message : messageSeparated) {
        if (message.contains(dataIdentifier))
            return message.remove(dataIdentifier + ":");
    }

    // If the data isn't in the message, returns an empty QString
    return QString();
}

void MessageProcessHandler::processMessage(QString message) {
    qDebug() << "Server App: Message to process: " << message;

    // Separates the message
    QRegularExpression separator;
    separator.setPattern(";");
    QStringList separated = message.split(separator);
    separator.setPattern(",");

    QString type = getMessageData(separated, "type");
    QString lobbyID = QString();
    QString senderID = QString();
    QString payLoad = QString();

    //type:createGame;payLoad:0000;senderID:1234
    if (type == "createGame") {
        qDebug() << "Create game request";

        senderID = getMessageData(separated, "senderID");
        if (!senderID.isEmpty())
            emit createGameRequest(senderID);
    }

    //type:joinGame;payLoad:1234;sender:5678
    else if (type == "joinGame") {
        qDebug() << "Join game request";

        lobbyID = getMessageData(separated, "payLoad");
        senderID = getMessageData(separated, "senderID");

        if (!lobbyID.isEmpty() && !senderID.isEmpty())
            emit joinGameRequest(lobbyID, senderID);
    }

    //type:message;payLoad:HelloLobby;lobbyID:1234senderID:5678
    else if (type == "message") {
        qDebug() << "Lobby message request";

        payLoad = getMessageData(separated, "payLoad");
        lobbyID = getMessageData(separated, "lobbyID");
        senderID = getMessageData(separated, "senderID");

        if (!payLoad.isEmpty() && !lobbyID.isEmpty() && !senderID.isEmpty())
            emit messageLobbyRequest(payLoad, lobbyID, senderID);
    }
}
