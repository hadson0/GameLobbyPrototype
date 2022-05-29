#include "userlistviewitem.h"

UserListViewItem::UserListViewItem(QString nickname, QWidget *parent)
    : BackgroundedFrame{parent}, defaultColor(172, 170, 177), readyColor(57, 153, 72), ready(false) {
    setColor(defaultColor);

    // Label
    nicknameLabel = new CustomLabel(nickname, this);
    nicknameLabel->setStyleSheet("*{color: #E3DDF0}");

    this->show();
}


void UserListViewItem::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Lobby ID Label
    int lobbyIDLabelWidth = this->getAvaliableWidth(), lobbyIDLabelHeight = this->getAvaliableHeight();
    int lobbyIDLabelX = 0, lobbyIDLabelY = 0;
    nicknameLabel->setFontSize(lobbyIDLabelHeight * 0.85);
    nicknameLabel->setGeometry(lobbyIDLabelX, lobbyIDLabelY, lobbyIDLabelWidth, lobbyIDLabelHeight);
}

bool UserListViewItem::isReady() { return ready; }

void UserListViewItem::setReady(bool ready) {
    // Changes color depending on whether it's ready or not
    QColor color = (ready) ? readyColor : defaultColor;
    setColor(color);

    this->ready = ready;    
    this->update();
}


