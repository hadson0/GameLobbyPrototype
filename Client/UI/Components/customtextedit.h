#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class CustomTextEdit : public QTextEdit {
    Q_OBJECT

    QFont fontAux; // Auxiliar variable to manage the label text font

    void keyPressEvent(QKeyEvent *event);

public:
    explicit CustomTextEdit(QWidget *parent = nullptr);

signals:
    void onEnterPressed();
};

#endif // CUSTOMTEXTEDIT_H
