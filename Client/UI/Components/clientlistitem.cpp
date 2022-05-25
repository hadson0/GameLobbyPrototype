#include "clientlistitem.h"

ClientListItem::ClientListItem(QString nickname, QWidget *parent)
    : BackgroundedFrame{parent}, defaultColor(172, 170, 177), readyColor(57, 153, 72), ready(false) {
    setColor(defaultColor);

    // Label
    clientIDLabel = new CustomLabel(nickname, this);
    clientIDLabel->setStyleSheet("*{color: #E3DDF0}");

    this->show();
}


void ClientListItem::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Lobby ID Label
    int lobbyIDLabelWidth = this->getAvaliableWidth(), lobbyIDLabelHeight = this->getAvaliableHeight();
    int lobbyIDLabelX = 0, lobbyIDLabelY = 0;
    clientIDLabel->setFontSize(lobbyIDLabelHeight * 0.85);
    clientIDLabel->setGeometry(lobbyIDLabelX, lobbyIDLabelY, lobbyIDLabelWidth, lobbyIDLabelHeight);
}

bool ClientListItem::isReady() { return ready; }

void ClientListItem::setReady(bool ready) {
    // Changes color depending on whether it's ready or not
    QColor color = (ready) ? readyColor : defaultColor;
    setColor(color);

    this->ready = ready;    
    this->update();
}


