#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject {
    Q_OBJECT

    QString clientID, nickname;
    bool ready;

public:
    explicit User(QString clientID, QString nickname = "", QObject *parent = nullptr);

    // Getters
    bool isReady();
    QString getClientID();
    QString getNickname();

    // Setters
    void setReady(bool ready);
    void setClientID(QString clientID);
    void setNickname(QString nickname);

signals:

};

#endif // USER_H
