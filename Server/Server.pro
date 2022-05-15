QT -= gui
QT += websockets

CONFIG += c++17 console
CONFIG -= app_bundle


SOURCES += \
        gamemanager.cpp \
        lobbyhandler.cpp \
        main.cpp \
        messageprocesshandler.cpp \
        websockethandler.cpp
        main.cpp \

HEADERS += \
        gamemanager.h \
        lobbyhandler.h \
        messageprocesshandler.h \
        websockethandler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
