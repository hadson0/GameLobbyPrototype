#include "messageprocessorhandler.h"

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
    qDebug() << "Client App: Message to process: " << message;

    // Separates the message
    QRegularExpression separator;
    separator.setPattern(";");
    QStringList separated = message.split(separator);
    separator.setPattern(",");

    QString type = getMessageData(separated, "type");
    QString clientID = QString();
    QString lobbyID = QString();       
    QStringList clientList = QStringList();
    QString lobbyMessage = QString();
    QString senderID = QString();

    //type:uniqueId;payLoad:1234
    if (type == "uniqueID") {
        qDebug() << "Client App: unique ID registration";

        clientID = getMessageData(separated, "payLoad");
        if (!clientID.isEmpty())
            emit uniqueIDRegistration(clientID);        
    }

    //type:newLobbyCreated;payLoad:1234;clientList:4312,856,5678
    else if (type == "newLobbyCreated" || type == "joinSuccess") {
        lobbyID = getMessageData(separated, "payLoad");
        clientList = getMessageData(separated, "clientList").split(separator);

        qDebug() << "Client App: Clients in lobby: " << clientList;

        if (!lobbyID.isEmpty() && !clientList.isEmpty())
            emit newLobby(lobbyID, clientList);
    }

    //type:updatedClientList;payLoad:1234,5678,4444
    else if (type == "updatedClientList") {
        qDebug() << "Client App: Received updated client list";

        clientList = getMessageData(separated, "payLoad").split(separator);;

        if (!clientList.isEmpty())
            emit lobbyListUpdated(clientList);
    }

    //type:lobbyMessage;payLoad:HelloWorld;senderID:1234
    else if (type == "lobbyMessage") {
        qDebug() << "Client App: New lobby message received";

        lobbyMessage = getMessageData(separated, "lobbyMessage");
        senderID = getMessageData(separated, "senderID");

        QString displayMessage = senderID + ": " + lobbyMessage;

        if (!lobbyMessage.isEmpty() && !senderID.isEmpty())
            emit newLobbyMessage(displayMessage);
    }
}
