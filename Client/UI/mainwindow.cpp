#include "mainwindow.h"

MainWindow::MainWindow(GameManager *gameManager, QWidget *parent)
    : QMainWindow(parent), gameManager(gameManager) {
    // Set window proprieties    
    this->setFixedSize(width, height);
    setWindowTitle("Game Lobby Prototype");

    displayScreen("MainMenuScreen");
}

void MainWindow::displayScreen(QString destinationScreen) {
    Screen *newScreen = nullptr;

    // Creates the screen, according to its class, and connects it
    if (destinationScreen == "MainMenuScreen") {
        newScreen = new MainMenuScreen(this);
        connect(newScreen, &MainMenuScreen::screenChanged, this, &MainWindow::displayScreen);
    }
    else if (destinationScreen == "SelectionScreen") {
        newScreen = new SelectionScreen(gameManager, this);
        connect(newScreen, &SelectionScreen::screenChanged, this, &MainWindow::displayScreen);
    }
    else if (destinationScreen == "JoinLobbyScreen") {
        newScreen = new JoinLobbyScreen(gameManager, this);
        connect(newScreen, &JoinLobbyScreen::screenChanged, this, &MainWindow::displayScreen);
    }
    else if (destinationScreen.contains("LobbyScreen:")) {
        QString lobbyID = destinationScreen.remove("LobbyScreen:");

        if (!lobbyID.isEmpty()) {
            newScreen = new LobbyScreen(lobbyID, gameManager, this);
            connect(newScreen, &LobbyScreen::screenChanged, this, &MainWindow::displayScreen);
        }
    }

    // If the screen was created, displays the screen
    if (newScreen != nullptr) {
        if (destinationScreen.contains("LobbyScreen:")) {
            lobbyScreen = newScreen;
            lobbyScreen->show();
        } else {
            currentMenuScreen = newScreen;
            currentMenuScreen->show();
        }
    } else {
        qDebug() << "Error while navigating through the screens. Destination: " + destinationScreen;
    }
}

