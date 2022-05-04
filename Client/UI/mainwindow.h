#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QApplication>

#include "Controllers/gamemanager.h"
#include "Screens/mainmenuscreen.h"
#include "Screens/selectionscreen.h"
#include "Screens/lobbyscreen.h"
#include "Screens/joinlobbyscreen.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    const int width = 1200, height = 675;

    Screen *currentMenuScreen, *lobbyScreen;

    GameManager *gameManager;

public:
    MainWindow(GameManager *gameManager, QWidget *parent = nullptr);


public slots:
    void displayScreen(QString targetScreen);
};
#endif // MAINWINDOW_H
