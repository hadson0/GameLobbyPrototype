QT += quick websockets
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Controllers/messageprocessorhandler.cpp \
    Controllers/websockethandler.cpp \
    UI/custombutton.cpp \
    UI/mainmenuwindow.cpp \
    main.cpp \

HEADERS += \
    Controllers/messageprocessorhandler.h \
    Controllers/websockethandler.h \
    UI/custombutton.h \
    UI/mainmenuwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
