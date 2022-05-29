#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <typeinfo>

#include <QDebug>
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include <QStack>
#include <QMessageBox>
#include <QCloseEvent>

#include "Controllers/gamemanager.h"
#include "Controllers/websockethandler.h"

#include "Screens/mainmenuscreen.h"
#include "Screens/selectionscreen.h"
#include "Screens/lobbyscreen.h"
#include "Screens/joinlobbyscreen.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    // Screens
    QStack<Screen *> menuScreenStack;
    LobbyScreen *lobbyScreen;

    GameManager *gameManager;
    WebSocketHandler *webSocketHandler;

    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);

    void displayMenuScreen(QString targetScreen);
    void displayLobbyScreen(QString lobbyID);
    void closeAllScreens();
    void onErrorOccurrence(QString error);

public slots:
    void onBackRequested();
    void onConnectToServerRequest();
    void onClientConnected();
    void onClientDisconnected();
};

#endif // MAINWINDOW_H
