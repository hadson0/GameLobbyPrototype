#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class CustomLineEdit : public QLineEdit {
    Q_OBJECT

    //QFont fontAux; // Auxiliar variable to manage the label text font

    void keyPressEvent(QKeyEvent *event);
    //void resizeEvent(QResizeEvent *event);

public:
    explicit CustomLineEdit(QWidget *parent = nullptr);

signals:
    void onEnterPressed();
};

#endif // CUSTOMLINEEDIT_H
