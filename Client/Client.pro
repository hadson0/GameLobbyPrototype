QT += quick websockets
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Controllers/messageprocessorhandler.cpp \
    Controllers/websockethandler.cpp \
    main.cpp \
    UI/mainwindow.cpp \

HEADERS += \
    Controllers/messageprocessorhandler.h \
    Controllers/websockethandler.h \
    UI/mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
