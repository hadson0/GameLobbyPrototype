QT += quick websockets
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Controllers/gamemanager.cpp \
    Controllers/messageprocesshandler.cpp \
    Controllers/websockethandler.cpp \
    UI/Components/backgroundedframe.cpp \
    UI/Components/chatframe.cpp \
    UI/Components/customlabel.cpp \
    UI/Components/customlineedit.cpp \
    UI/Components/custompushbutton.cpp \
    UI/Components/customtextedit.cpp \
    UI/Components/nicknameinputdialog.cpp \
    UI/Components/userlistviewitem.cpp \
    UI/Components/userlistview.cpp \
    UI/Screens/joinlobbyscreen.cpp \
    UI/Screens/lobbyscreen.cpp \
    UI/Screens/screen.cpp \
    UI/Screens/mainmenuscreen.cpp \
    UI/Screens/selectionscreen.cpp \
    UI/mainwindow.cpp \
    main.cpp \


HEADERS += \
    Controllers/gamemanager.h \
    Controllers/messageprocesshandler.h \
    Controllers/websockethandler.h \
    UI/Components/backgroundedframe.h \
    UI/Components/chatframe.h \
    UI/Components/customlabel.h \
    UI/Components/customlineedit.h \
    UI/Components/custompushbutton.h \
    UI/Components/customtextedit.h \
    UI/Components/nicknameinputdialog.h \
    UI/Components/userlistviewitem.h \
    UI/Components/userlistview.h \
    UI/Screens/joinlobbyscreen.h \
    UI/Screens/lobbyscreen.h \
    UI/Screens/screen.h \
    UI/Screens/mainmenuscreen.h \
    UI/Screens/selectionscreen.h \
    UI/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
