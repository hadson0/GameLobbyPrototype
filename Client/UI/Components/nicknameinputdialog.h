#ifndef NICKNAMEINPUTDIALOG_H
#define NICKNAMEINPUTDIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "UI/Components/customlineedit.h"
#include "UI/Components/customlabel.h"

class NicknameInputDialog : public QDialog {
    Q_OBJECT

    // Widgets
    CustomLineEdit *input;
    QVBoxLayout *vbox;
    QDialogButtonBox * buttonBox;

    // Atributes
    QString nickname;

public:
    explicit NicknameInputDialog(QWidget *parent = nullptr);

    QString getText();

    static QString getNickname(QWidget *parent = nullptr);

public slots:
    void onOkClicked();
    void onCloseClicked();
};

#endif // NICKNAMEINPUTDIALOG_H
