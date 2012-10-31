#-------------------------------------------------
#
# Project created by QtCreator 2012-10-04T13:35:03
#
#-------------------------------------------------

QT       += core gui

TARGET = GraphicsEditor
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainscene.cpp \
    ndaalgorithm.cpp \
    undocommand.cpp

HEADERS  += widget.hpp \
    mainscene.hpp \
    algorithmInterface.hpp \
    ndaalgorithm.hpp \
    undocommand.hpp

RESOURCES += \
    resources.qrc
