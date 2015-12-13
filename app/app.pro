QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS += \
    SField.h \
    CTopWidget.h \
    CTableView.h \
    mainwindow.h \
    CSettingsDialog.h \
    SPreferences.h \
    CTableModel.h \
    Constants.h \
    CModel.h \
    CInactiveDelegate.h \
    CActiveDelegate.h

SOURCES += main.cpp \
    CSettingsDialog.cpp \
    CModel.cpp \
    CTableModel.cpp \
    CTableView.cpp \
    mainwindow.cpp \
    CTopWidget.cpp \
    CInactiveDelegate.cpp \
    CActiveDelegate.cpp

FORMS += \
    mainwindow.ui \
    CTopWidget.ui \
    CSettingsDialog.ui

CONFIG       += c++14
RESOURCES    += images.qrc
TRANSLATIONS += trans_pl.ts
