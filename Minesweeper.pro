QT += core gui widgets
CONFIG += c++11
CONFIG += c++20

SOURCES += \
    main.cpp \
    GameBoard.cpp \
    Cell.cpp

HEADERS += \
    GameBoard.h \
    Cell.h

TARGET = Minesweeper
TEMPLATE = app

# Remove app_bundle to avoid the macOS .app creation
CONFIG -= app_bundle
