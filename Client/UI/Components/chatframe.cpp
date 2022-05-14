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
    connect(chatInput, &CustomTextEdit::enterPressed, this, &ChatFrame::onSendButtonClicked);

    // Send Message button
    sendMessageButton = new CustomPushButton("Send", this);
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

    // Chat View
    int chatViewX = getPadding(), chatViewY = getPadding();
    int chatViewWidht = this->getAvaliableWidth(), chatViewHeight = (this->getAvaliableHeight()  - getPadding()) * 0.9;
    chatView->setGeometry(chatViewX, chatViewY, chatViewWidht, chatViewHeight);

    // Chat Input
    int chatInputX = getPadding(), chatInputY = chatViewHeight + 2 * getPadding();
    int chatInputWidht = this->getAvaliableWidth() * 0.9, chatInputHeight = this->getAvaliableHeight() - chatViewHeight  - getPadding();
    chatInput->setGeometry(chatInputX, chatInputY, chatInputWidht, chatInputHeight);

    // Send Message Button
    int buttonX = chatInputWidht + 2 * getPadding(), buttonY = chatInputY;
    int buttonWidth = this->getAvaliableWidth() - chatInputWidht - getPadding(), buttonHeight = chatInputHeight;
    sendMessageButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);
}

