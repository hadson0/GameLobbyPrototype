#include "mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton response = QMessageBox::question( this, "Close Game",
                                                                    "Are you sure you want to close the game?",
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (response != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
            webSocketHandler->deleteLater();
        }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Game Lobby Prototype");
    lobbyScreen = nullptr;

    // Maintains window aspect ratio
    QSizePolicy sizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(true);
    setSizePolicy(sizePolicy);   

    // Creates a Web Socket Handler
    webSocketHandler = WebSocketHandler::getInstance(this);
    connect(webSocketHandler, &WebSocketHandler::connectionError, this, &MainWindow::onClientDisconnected);

    // Creates a game manager and connects it to the Web Socket Handler
    gameManager = GameManager::getInstance(this);
    connect(webSocketHandler, &WebSocketHandler::newMessageReadyForProcessing, gameManager, &GameManager::processSocketMessage);
    connect(gameManager, &GameManager::newMessageReadyToSend, webSocketHandler, &WebSocketHandler::sendMessageToServer);
    connect(gameManager, &GameManager::lobbyIDChanged, this, &MainWindow::displayLobbyScreen);
    connect(gameManager, &GameManager::clientConnected, this, &MainWindow::onClientConnected);
    connect(gameManager, &GameManager::error, this, &MainWindow::onErrorOccurrence);
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
        connect(newScreen, &Screen::error, this, &MainWindow::onErrorOccurrence);

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
    connect(lobbyScreen, &Screen::error, this, &MainWindow::onErrorOccurrence);

    connect(gameManager, &GameManager::newLobbyMessageRecieved, lobbyScreen, &LobbyScreen::newMessageRecieved);
    connect(gameManager, &GameManager::userListChanged, lobbyScreen, &LobbyScreen::userListChanged);
    connect(gameManager, &GameManager::readyListChanged, lobbyScreen, &LobbyScreen::readyListChanged);
    connect(gameManager, &GameManager::lobbyLeft, this, &MainWindow::onBackRequested);

    menuScreenStack.top()->hide();
    lobbyScreen->show();
}

void MainWindow::closeAllScreens() {
    // If the lobby screen is open, closes it
    if (lobbyScreen != nullptr) {
        gameManager->leaveLobby();
        lobbyScreen->deleteLater();
        lobbyScreen = nullptr; // Sets the lobbyScreen pointer to null, to avoid errors
    }

    // Closes all screens
    while (!menuScreenStack.isEmpty()) {
        delete menuScreenStack.top();
        menuScreenStack.pop();
    }

    webSocketHandler->close();
    this->displayMenuScreen("MainMenuScreen");
}

void MainWindow::onErrorOccurrence(QString errorCode) {
    // "joinError" || "quitError" || "lobbyMessageError" || "connectionError" || "nicknameError"
    if (errorCode == "joinError") {
        QMessageBox::warning(this, "Error", "An error occurred while trying to join the lobby");
    }

    else if (errorCode == "lobbyMessageError") {
        QMessageBox::warning(this, "Error", "An error occurred while trying to send a message to the lobby");
    }

    else if (errorCode == "blankNick") {
        QMessageBox::warning(this, "Error", "Nickname field cannot be left blank.");
    }

    else if (errorCode == "joinFieldsError") {
        QMessageBox::warning(this, "Error", "Please fill in all fields correctly.");
    }

    else if (errorCode == "existingNickError") {
        QMessageBox::warning(this, "Error", "This nickname is already being used in the lobby.\n"
                                            "Try a different one.");
    }

    else if (errorCode == "quitError") {
        QMessageBox::warning(this, "Error", "An unexpected error has occurred.\n "
                                                         "You will be disconnected from the lobby");
        closeAllScreens();
    }

    else if (errorCode == "connectionError") {
        QMessageBox::warning(this, "Error", "Connection to server failed.");
        closeAllScreens();
    }
}

// Goes to the previous screen
void MainWindow::onBackRequested() {
    // Deletes the current screen
    if (lobbyScreen != nullptr) { // If the current screen is the lobby screen
        gameManager->leaveLobby();
        delete lobbyScreen;
        lobbyScreen = nullptr; // Sets the lobbyScreen pointer to null, to avoid errors
    } else {
        delete menuScreenStack.top();
        menuScreenStack.pop();
    }

    menuScreenStack.top()->show();
}

void MainWindow::onConnectToServerRequest() {
    webSocketHandler->connectToServer("ws://127.0.0.1:8585");
}

void MainWindow::onClientConnected() {
    displayMenuScreen("SelectionScreen");
}

void MainWindow::onClientDisconnected() {
    this->onErrorOccurrence("connectionError");
}
