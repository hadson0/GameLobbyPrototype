#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel {
    Q_OBJECT

    QFont auxFont; // Auxiliar variable to manage the label text font

    void resizeEvent(QResizeEvent *event);

public:
    explicit CustomLabel(QString text = QString(), QWidget *parent = nullptr);

    // Getters
    int getFontSize();

    // Setters
    void setFontSize(int size);
};

#endif // CUSTOMLABEL_H
