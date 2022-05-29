#include "userlistview.h"


#include <QDebug>

UserListView::UserListView(QWidget *parent)
    : BackgroundedFrame{parent} {
    setPadding(10);
}

void UserListView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);    

    // Setup the painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor backgroundColor(75, 37, 150);

    // Draws the background
    QPainterPath backgroundPath;
    QPen pen(backgroundColor);
    painter.setPen(pen);
    backgroundPath.addRoundedRect(this->rect(), this->getBorderRadius(), this->getBorderRadius());
    painter.fillPath(backgroundPath, backgroundColor);
    painter.drawPath(backgroundPath);

    // Draws the list background
    QPainterPath listPath;
    QColor listColor(227, 221, 240);
    pen.setColor(listColor);
    painter.setPen(pen);
    listPath.addRoundedRect(this->getPadding(), this->getPadding(),
                        this->getAvaliableWidth(), this->getAvaliableHeight(),
                        this->getBorderRadius(), this->getBorderRadius());
    painter.fillPath(listPath,listColor);
    painter.drawPath(listPath);

    // User Item
    int clientX = 2 * this->getPadding(), clientY = clientX + 1;
    int clientWidth = this->getAvaliableWidth() - clientX, clientHeight = (this->getAvaliableHeight() - clientY) * 0.16;
    setSpacing((this->getAvaliableHeight() - clientY) * 0.008);

    // Draws in reversed order to display in the correct order
    QStringList clientIDList = userMap.keys();
    QStringList::reverse_iterator clientIt = clientIDList.rbegin();
    for (; clientIt != clientIDList.rend(); clientIt++) {
        userMap[*clientIt]->setGeometry(clientX, clientY, clientWidth, clientHeight);
        clientY += clientHeight + getSpacing();
    }
}

void UserListView::addUser(QString userNick) {
    if (!userMap.contains(userNick)) {
        userMap[userNick] = new UserListViewItem(userNick, this);
    }
}

void UserListView::removeUSer(QString clientID) {
    if (userMap.contains(clientID)) {
        userMap[clientID]->deleteLater();
        userMap.remove(clientID);
    }
}

void UserListView::setReady(QString userNick, bool ready) {
    if (userNick.contains(userNick)) {
        userMap[userNick]->setReady(ready);
    }
}

// Adds the clients to the list
void UserListView::onUserListChanged(QStringList newUserList) {

    // Removes the clients who left the lobby
    QStringList oldUserList = userMap.keys();
    for (const QString &userNick : oldUserList) {
        if (!userMap.contains(userNick)) {
            removeUSer(userNick);
        }
    }

    // Adds the new clients
    for (const QString &userNick : newUserList) {
        addUser(userNick);
    }

    this->update();
}

void UserListView::onReadyListChanged(QStringList newReadyList) {
    QMap<QString, UserListViewItem*>::iterator it = userMap.begin();
    for (; it != userMap.end(); it++) {
        it.value()->setReady(newReadyList.contains(it.key()));
    }

    this->update();
}

