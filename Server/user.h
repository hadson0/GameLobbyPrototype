#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject {
    Q_OBJECT

    QString nickname;
    bool ready;

public:
    explicit User(QString nickname, QObject *parent = nullptr);

    // Getters
    bool isReady();
    QString getNickname();

    // Setters
    void setReady(bool ready);
    void setNickname(QString nickname);
};

#endif // USER_H
