#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T18:00:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SheepSweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        CModel.cpp \
        CFieldDelegate.cpp \
        CTableModel.cpp \
        CTableView.cpp \
        CTopWidget.cpp \
        CSettingsDialog.cpp

HEADERS  += mainwindow.h \
        CModel.h \
        CFieldDelegate.h \
        SField.h \
        CTableModel.h \
        CTableView.h \
        CTopWidget.h \
    	Constants.h \
        CSettingsDialog.h

FORMS    += mainwindow.ui \
        CTopWidget.ui \
        CSettingsDialog.ui

CONFIG   += c++14

RESOURCES += \
        images.qrc
