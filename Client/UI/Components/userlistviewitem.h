#ifndef USERLISTVIEWITEM_H
#define USERLISTVIEWITEM_H

#include "backgroundedframe.h"
#include "customlabel.h"

class UserListViewItem : public BackgroundedFrame {
    Q_OBJECT

    CustomLabel *nicknameLabel;
    QColor defaultColor, readyColor;
    bool ready;

    void resizeEvent(QResizeEvent *event);

public:
    explicit UserListViewItem(QString nickname, QWidget *parent = nullptr);

    // Getters
    bool isReady();

    // Setters
    void setReady(bool ready);

    // Methods
    void setHighlighted();
};

#endif // USERLISTVIEWITEM_H
