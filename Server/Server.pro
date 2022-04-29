QT -= gui
QT += websockets

CONFIG += c++17 console
CONFIG -= app_bundle


SOURCES += \
        gamelobbyhandler.cpp \
        gamemanager.cpp \
        main.cpp \
        messageprocesshandler.cpp \
        websockethandler.cpp
        main.cpp \

HEADERS += \
        gamelobbyhandler.h \
        gamemanager.h \
        messageprocesshandler.h \
        websockethandler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
