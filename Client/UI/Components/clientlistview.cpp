#include "clientlistview.h"


#include <QDebug>

ClientListView::ClientListView(QWidget *parent)
    : BackgroundedFrame{parent} {
    setPadding(10);    
}

void ClientListView::paintEvent(QPaintEvent *event) {
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

    // Client Item
    int clientX = 2 * this->getPadding(), clientY = clientX + 1;
    int clientWidth = this->getAvaliableWidth() - clientX, clientHeight = (this->getAvaliableHeight() - clientY) * 0.16;
    setSpacing((this->getAvaliableHeight() - clientY) * 0.008);

    // Draws in reversed order to display in the correct order
    QStringList clientIDList = clientMap.keys();
    QStringList::reverse_iterator clientIt = clientIDList.rbegin();
    for (; clientIt != clientIDList.rend(); clientIt++) {
        clientMap[*clientIt]->setGeometry(clientX, clientY, clientWidth, clientHeight);
        clientY += clientHeight + getSpacing();
    }
}

void ClientListView::addClientItem(QString clientID, bool highlighted) {
    // Just adds the client if he isn't already here
    if (!clientMap.contains(clientID)) {
        clientMap[clientID] = new ClientListItem(clientID, highlighted, this);;
    }
}

void ClientListView::setReady(QString clientID, bool ready) {
    if (clientID.contains(clientID)) {
        clientMap[clientID]->setReady(ready);
    }
}

// Adds the clients to the list
void ClientListView::onClientListChanged(QStringList clientIDList) {
    for (qsizetype i = 0; i < clientIDList.size(); i++) {
        addClientItem(clientIDList[i]);
    }

    this->update();
}

void ClientListView::onReadyListChanged(QStringList newReadyList) {
    QMap<QString, ClientListItem*>::iterator it = clientMap.begin();
    for (; it != clientMap.end(); it++) {
        it.value()->setReady(newReadyList.contains(it.key()));
    }

    this->update();
}

