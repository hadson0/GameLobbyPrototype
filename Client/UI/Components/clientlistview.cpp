#include "clientlistview.h"

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

void ClientListView::toggleReady(QString clientID) {
    if (clientID.contains(clientID)) {
        clientMap[clientID]->toggleReady();
    }
}

// Adds the clients to the list
void ClientListView::onClientListChanged(QStringList clientIDList) {
    // The first client in the list is the host, so he is highlighted
    addClientItem(clientIDList[0], true);

    // Adds the rest of the clients
    for (qsizetype i = 1; i < clientIDList.size(); i++) {
        addClientItem(clientIDList[i]);
    }

    // After adding all the clients, update the frame
    this->update();
}

