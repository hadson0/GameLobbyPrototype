#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel {
    Q_OBJECT

    QFont fontAux; // Auxiliar variable to manage the label text font

public:
    explicit CustomLabel(QString text = QString(), QWidget *parent = nullptr);

    void setFontSize(int size);
};

#endif // CUSTOMLABEL_H
