TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Game.cpp \
        board.cpp \
        main.cpp

LIBS += -L"path"

CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

INCLUDEPATH += "N:/SFML-2.5.1/include"
DEPENDPATH += "N:/SFML-2.5.1/include"

HEADERS += \
    Game.h \
    board.h

