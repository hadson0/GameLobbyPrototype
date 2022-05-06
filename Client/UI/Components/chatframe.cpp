#include "chatframe.h"

#include <QDebug>

ChatFrame::ChatFrame(QWidget *parent)
    : BackgroundedFrame{parent} {
    setPadding(10);

    // Chat View
    chatView = new CustomTextEdit(this);
    chatView->setReadOnly(true);

    // Chat Input
    chatInput = new CustomTextEdit(this);

    // Send Message button
    sendMessageButton = new QPushButton("Send", this);
    sendMessageButton->setStyleSheet("* {background-color: #E3DDF0; border: 0px;}");
    connect(sendMessageButton, &QPushButton::clicked, this, &ChatFrame::onSendButtonClicked);

}

void ChatFrame::onSendButtonClicked() {
    QString message = chatInput->toPlainText();
    chatInput->clear();
    emit sendMessage(message);
}

void ChatFrame::onMessageRecieved(QString message) {
    chatView->append(message);
}

void ChatFrame::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    // Avaliable size
    int avaliableHeight = this->height() - 3 * getPadding(), avaliableWidth = this->width() - 2 * getPadding();

    // Chat View
    int chatViewX = getPadding(), chatViewY = getPadding();
    int chatViewWidht = avaliableWidth, chatViewHeight = avaliableHeight * 0.9;
    chatView->setGeometry(chatViewX, chatViewY, chatViewWidht, chatViewHeight);

    // Chat Input
    int chatInputX = getPadding(), chatInputY = chatViewHeight + 2 * getPadding();
    int chatInputWidht = avaliableWidth * 0.9, chatInputHeight = avaliableHeight - chatViewHeight;
    chatInput->setGeometry(chatInputX, chatInputY, chatInputWidht, chatInputHeight);

    // Send Message Button
    int buttonX = chatInputWidht + 2 * getPadding(), buttonY = chatInputY;
    int buttonWidth = avaliableWidth - chatInputWidht - getPadding(), buttonHeight = chatInputHeight;
    sendMessageButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

