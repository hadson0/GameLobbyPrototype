#ifndef CHATFRAME_H
#define CHATFRAME_H

#include "backgroundedframe.h"
#include "UI/Components/customtextedit.h"
#include "UI/Components/custompushbutton.h"

class ChatFrame : public BackgroundedFrame {
    Q_OBJECT

    // Widgets
    CustomTextEdit *chatView, *chatInput;
    CustomPushButton *sendMessageButton;

    void resizeEvent(QResizeEvent *event);

public:
    explicit ChatFrame(QWidget *parent = nullptr);    

public slots:
    void onSendButtonClicked();
    void onMessageRecieved(QString message);

signals:
    void sendMessage(QString message);
};

#endif // CHATFRAME_H
