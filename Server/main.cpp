#include <QCoreApplication>
#include "gamemanager.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    GameManager gameManager;

    return a.exec();
}
