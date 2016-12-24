#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T06:59:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvertedSearchEngine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    crawler.cpp \
    bst.cpp \
    tree.cpp \
    log.cpp \
    stack.cpp \
    terminal.cpp \
    stoptree.cpp \
    tst.cpp \
    trie.cpp \
    cmdline.cpp \
    progressbar.cpp

HEADERS  += mainwindow.h \
    crawler.h \
    bst.h \
    tree.h \
    log.h \
    stack.h \
    terminal.h \
    stoptree.h \
    tst.h \
    trie.h \
    cmdline.h \
    progressbar.h

FORMS    += mainwindow.ui
