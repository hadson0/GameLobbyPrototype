#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Game Lobby Prototype");

    lobbyScreen = nullptr;

    gameManager = new GameManager;

    // Creates a Web Socket Handler and connects it to the server
    webSocketHandler = new WebSocketHandler(this);
    webSocketHandler->connectToServer("ws://127.0.0.1:8585");

    // Connects the Web Socket Handler to the Game Manager and to this screen
    connect(webSocketHandler, &WebSocketHandler::newMessageReadyForProcessing, gameManager, &GameManager::processSocketMessage);    
    connect(gameManager, &GameManager::newMessageReadyToSend, webSocketHandler, &WebSocketHandler::sendMessageToServer);
    connect(gameManager, &GameManager::lobbyIDChanged, this, &MainWindow::displayLobbyScreen);

    displayMenuScreen("MainMenuScreen");
}

// Hides the old screen and display the one mentioned in the argument
void MainWindow::displayMenuScreen(QString destinationMenuScreen) {
    Screen *newScreen = nullptr;

    if (destinationMenuScreen == "MainMenuScreen")
        newScreen = new MainMenuScreen(this);
    else if (destinationMenuScreen == "SelectionScreen")
        newScreen = new SelectionScreen(this);
    else if (destinationMenuScreen == "JoinLobbyScreen")
        newScreen = new JoinLobbyScreen(this);

    // If the screen was created successfully, deletes the old screen and displays the current one
    if (newScreen != nullptr) {
        connect(newScreen, &Screen::backRequest, this, &MainWindow::onBackRequested);
        connect(newScreen, &Screen::quitApplicationRequest, this, &MainWindow::onQuitApplicationRequested);
        connect(newScreen, &Screen::sendRequestMessage, gameManager, &GameManager::processScreenMessage);
        connect(newScreen, &Screen::displayMenuScreenRequest, this, &MainWindow::displayMenuScreen);

        if (!menuScreenStack.isEmpty())
            menuScreenStack.top()->hide();

        menuScreenStack.push(newScreen);
        menuScreenStack.top()->show();
    }
    else
        qDebug() << "Error while displaying the screen: " + destinationMenuScreen;

}

// Creates the lobby screen and connects it
void MainWindow::displayLobbyScreen(QString lobbyID) {
    lobbyScreen = new LobbyScreen(lobbyID, this);

    connect(lobbyScreen, &Screen::backRequest, this, &MainWindow::onBackRequested);
    connect(lobbyScreen, &Screen::sendRequestMessage, gameManager, &GameManager::processScreenMessage);
    connect(lobbyScreen, &Screen::displayMenuScreenRequest, this, &MainWindow::displayMenuScreen);
    connect(gameManager, &GameManager::newLobbyMessageRecieved, lobbyScreen, &LobbyScreen::newMessageRecieved);

    menuScreenStack.top()->hide();
    lobbyScreen->show();
}

// Goes to the previous screen
void MainWindow::onBackRequested() {
    // Deletes the current screen
    if (lobbyScreen != nullptr) { // If the current screen is the lobby screen
        delete lobbyScreen;
    } else {
        delete menuScreenStack.top();
        menuScreenStack.pop();
    }

    // Shows the previous screen
    menuScreenStack.top()->show();
}

// Quits the application
void MainWindow::onQuitApplicationRequested() {
    QApplication::quit();
}


