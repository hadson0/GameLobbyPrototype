#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Game Lobby Prototype");
    lobbyScreen = nullptr;

    // Maintains window aspect ratio
    QSizePolicy sizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(true);
    setSizePolicy(sizePolicy);   

    // Creates a Web Socket Handler and connects it to the server
    webSocketHandler = new WebSocketHandler(this);    

    // Creates a game manager and connects it to the Web Socket Handler
    gameManager = new GameManager(this);
    connect(webSocketHandler, &WebSocketHandler::newMessageReadyForProcessing, gameManager, &GameManager::processSocketMessage);
    connect(gameManager, &GameManager::newMessageReadyToSend, webSocketHandler, &WebSocketHandler::sendMessageToServer);
    connect(gameManager, &GameManager::lobbyIDChanged, this, &MainWindow::displayLobbyScreen);
    connect(gameManager, &GameManager::clientConnected, this, &MainWindow::onClientConnected);
}

// Hides the old screen and display the one mentioned in the argument
void MainWindow::displayMenuScreen(QString destinationMenuScreen) {
    Screen *newScreen = nullptr;

    if (destinationMenuScreen == "MainMenuScreen") {
        newScreen = new MainMenuScreen(this);
        connect(qobject_cast<MainMenuScreen *>(newScreen), &MainMenuScreen::connectToTheServerRequest, this, &MainWindow::onConnectToServerRequest);
    } else if (destinationMenuScreen == "SelectionScreen") {
        newScreen = new SelectionScreen(this);
    } else if (destinationMenuScreen == "JoinLobbyScreen") {
        newScreen = new JoinLobbyScreen(this);
    }

    // If the screen was created successfully, deletes the old screen and displays the current one
    if (newScreen != nullptr) {
        connect(newScreen, &Screen::backRequest, this, &MainWindow::onBackRequested);
        connect(newScreen, &Screen::quitAppRequest, this, &QApplication::quit);
        connect(newScreen, &Screen::sendRequestMessage, gameManager, &GameManager::processScreenMessage);
        connect(newScreen, &Screen::menuScreenDisplayRequest, this, &MainWindow::displayMenuScreen);

        if (!menuScreenStack.isEmpty()) {
            menuScreenStack.top()->hide();
        }

        menuScreenStack.push(newScreen);
        menuScreenStack.top()->show();
    }
}

// Creates the lobby screen and connects it
void MainWindow::displayLobbyScreen(QString lobbyID) {
    lobbyScreen = new LobbyScreen(lobbyID, this);

    connect(lobbyScreen, &Screen::backRequest, this, &MainWindow::onBackRequested);
    connect(lobbyScreen, &Screen::sendRequestMessage, gameManager, &GameManager::processScreenMessage);
    connect(lobbyScreen, &Screen::menuScreenDisplayRequest, this, &MainWindow::displayMenuScreen);

    connect(gameManager, &GameManager::newLobbyMessageRecieved, lobbyScreen, &LobbyScreen::newMessageRecieved);
    connect(gameManager, &GameManager::clientListChanged, lobbyScreen, &LobbyScreen::clientListChanged);
    connect(gameManager, &GameManager::readyListChanged, lobbyScreen, &LobbyScreen::readyListChanged);
    connect(gameManager, &GameManager::lobbyLeft, this, &MainWindow::onBackRequested);

    menuScreenStack.top()->hide();
    lobbyScreen->show();
}

// Goes to the previous screen
void MainWindow::onBackRequested() {
    // Deletes the current screen
    if (lobbyScreen != nullptr) { // If the current screen is the lobby screen
        // Asks the user if he wants to leave the lobby
        int answer = QMessageBox::warning(this, "Leave lobby", "Are you sure you want to leave the lobby?",
                                       QMessageBox::Ok | QMessageBox::Cancel);

        if (answer == QMessageBox::Ok) {
            delete lobbyScreen;
            lobbyScreen = nullptr; // Sets the lobbyScreen pointer to null, to avoid errors
            menuScreenStack.top()->show();
        }
    } else {
        delete menuScreenStack.top();
        menuScreenStack.pop();
        menuScreenStack.top()->show();
    }
}

void MainWindow::onConnectToServerRequest() {
    try {
        webSocketHandler->connectToServer("ws://127.0.0.1:8585");
    } catch (int e) {
        QMessageBox::warning(this, "Error", "Connection to the server has failed.");
    }
}

void MainWindow::onClientConnected() {
    displayMenuScreen("SelectionScreen");
}
