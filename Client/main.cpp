#include <QApplication>
#include <QFile>

#include "UI/mainwindow.h"
#include "Controllers/websockethandler.h"
#include "Controllers/gamemanager.h"

const QString getStyleSheet();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WebSocketHandler webSocketHandler;
    webSocketHandler.connectToServer("ws://127.0.0.1:8585");

    GameManager gameManager;

    QObject::connect(&webSocketHandler, &WebSocketHandler::newMessageReadyForProcessing, &gameManager, &GameManager::processSocketMessage);
    QObject::connect(&gameManager, &GameManager::newMessageReadyToSend, &webSocketHandler, &WebSocketHandler::sendMessageToServer);

    MainWindow mainWindow(&gameManager);
    mainWindow.setStyleSheet(getStyleSheet());

    // Moves the window to the center of the screen
    int screenWidth = mainWindow.screen()->geometry().width();
    int screenHeight = mainWindow.screen()->geometry().height();
    mainWindow.move((screenWidth / 2) - (mainWindow.geometry().width() / 2),
           (screenHeight / 2) - (mainWindow.geometry().height() / 2));

    mainWindow.show();

    return a.exec();
}

// Sets the syle of the application (MainWindow)
const QString getStyleSheet() {
    /**
        I chose to make a function that just returns a constant QString because the style sheet is quite big
        and it wouldn't be very organized to leave at the beginning of the code.
        There are more solutions, one of them would be to read it from a file, but I preferred to do it this way because it's simpler
    **/
    const int borderRadius = 15;
    const QString styleSheet =
            "QMainWindow {"
                "color: qlineargradient(spread:pad, x1:0 y1:1, x2:1 y2:0,"
                "stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #6C14A8, stop:1 #6A4BE4);"
            "}"

            "QLabel {"
                "color: white;"
                "font-weight: bold;"
                "text-align: center"
            "}"

            "QPushButton {"
                "background-color: white; "
                "border-radius: " + QString::number(borderRadius) + "px; "
                "border: 2px solid #110C5A;"
                "color: #110C5A;"
                "font-weight: bold;"
            "}"            
            "QPushButton:pressed {"
                "background-color: #CABFE0;"
            "}"

            "QTextEdit {"
                "background-color: #E3DDF0; border-radius: " + QString::number(borderRadius) + "px;"
                "padding: 5px;"
                "color: #110C5A;"
                "font-size: 20px"
            "}"

            "QLineEdit {"
                "background-color: #E3DDF0; border-radius: " + QString::number(borderRadius) + "px;"
                "padding: 5px;"
                "color: #110C5A;"
            "}"

            "QScrollBar {"
                "border: none;"
            "}"
           " QScrollBar::handle {"
                "background-color: #807E85;"
                "min-width: 20px;"
                "min-height: 20px;"
            "}"
            "QScrollBar::vertical {"
                "width: 5px;"
            "}"
            "QScrollBar::horizontal {"
               " height: 5px;"
           " }"
            "QScrollBar::add-line {"
                "border: none;"
                "background: none;"
            "}"
            "QScrollBar::sub-line {"
                "border: none;"
                "background: none;"
            "};";

    return styleSheet;
}
