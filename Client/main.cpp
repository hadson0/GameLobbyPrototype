#include <QApplication>
#include <QFile>

#include "UI/mainwindow.h"

const QString getStyleSheet();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;

    // Main Window size and position
    int mainWindowWidth = 1200, mainWindowHeight = 675;
    mainWindow.setFixedSize(mainWindowWidth, mainWindowHeight);

    mainWindow.setStyleSheet(getStyleSheet());
    mainWindow.displayMenuScreen("MainMenuScreen");
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
    const QString styleSheet =
            "QMainWindow {"
                "color: qlineargradient(spread:pad, x1:0 y1:1, x2:1 y2:0,"
                "stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 #7d20bd, stop:1 #8165f0);"
            "}"

            "QLineEdit {"
                "background-color: #E3DDF0; border-radius: 15px;"
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
