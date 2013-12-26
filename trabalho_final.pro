#-------------------------------------------------
#
# Project created by QtCreator 2013-12-20T11:06:49
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trabalho_final
TEMPLATE = app

LIBS += -L/usr/local/lib -lassimp -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    teste.cpp \
    object.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    teste.h \
    object.h

FORMS    += mainwindow.ui

OTHER_FILES += assets/*
