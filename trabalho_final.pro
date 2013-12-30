#-------------------------------------------------
#
# Project created by QtCreator 2013-12-20T11:06:49
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trabalho_final
TEMPLATE = app

# Libs e include p/ MacOSX com assimp instalado pelo brew
LIBS += -L/usr/local/Cellar/assimp/3.0.1270/lib -lassimp
INCLUDEPATH += /usr/local/Cellar/assimp/3.0.1270/include

# Libs p/ Linux com assimp instalado no /usr/local
#LIBS += -L/usr/local/lib -lassimp -lGLU

SOURCES += main.cpp\
        mainwindow.cpp \
    gldisplay.cpp \
    object.cpp

HEADERS  += mainwindow.h \
    gldisplay.h \
    object.h

FORMS    += mainwindow.ui

OTHER_FILES += assets/*
