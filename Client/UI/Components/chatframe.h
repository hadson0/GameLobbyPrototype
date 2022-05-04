#ifndef CHATFRAME_H
#define CHATFRAME_H

#include <QPushButton>

#include "backgroundedframe.h"
#include "UI/Components/customtextedit.h"

class ChatFrame : public BackgroundedFrame {
    Q_OBJECT

    int margin;
    void resizeEvent(QResizeEvent *event);

public:
    explicit ChatFrame(QWidget *parent = nullptr);

    CustomTextEdit *chatView, *chatInput;
    QPushButton *sendMessageButton;

public slots:
    void onSendButtonClicked();
    void onMessageRecieved(QString message);

signals:
    void sendMessage(QString message);
};

#endif // CHATFRAME_H
