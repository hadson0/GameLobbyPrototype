#include "clientlistitem.h"

ClientListItem::ClientListItem(QString uniqueID, bool highlighted, QWidget *parent)
    : BackgroundedFrame{parent}, defaultColor(172, 170, 177), readyColor(45, 173, 65), ready(false) {
    // If this is te client, the color is different
    if (highlighted) defaultColor.setRgb(137, 123, 173);
    setColor(defaultColor);

    // Label
    clientIDLabel = new CustomLabel(uniqueID, this);
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

void ClientListItem::toggleReady() {
    // true <-> false
    ready = !ready;

    // Changes color depending on whether it's ready or not
    QColor color = (ready) ? readyColor : defaultColor;
    setColor(color);
}


