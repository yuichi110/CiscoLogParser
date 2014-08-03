#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T21:18:11
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CiscoLogParser
TEMPLATE = app

# Windows
RC_ICONS = appicon.ico

# Mac
ICON = appicon.icns

SOURCES += \
    mwc_mainwindow.cpp \
    core_main.cpp \
    mwc_productpicker.cpp \
    mwc_dropzone.cpp \
    core_messagebroker.cpp \
    log_abstractlogparser.cpp \
    log_nexuslogparser.cpp \
    core_productmanager.cpp \
    core_appinfo.cpp \
    test_componenttester.cpp \
    json_jsonparser.cpp \
    json_productrule.cpp \
    window_jsontestwidget.cpp \
    window_jsontextedit.cpp \
    mwc_menubar.cpp \
    window_windowmanager.cpp \
    mwc_progressdialog.cpp \
    window_aboutwidget.cpp \
    window_preferencewidget.cpp \
    core_preferencemanager.cpp \
    dao_preferencedataaccessor.cpp \
    dao_clvdataaccessor.cpp

HEADERS  += \
    mwc_mainwindow.h \
    mwc_productpicker.h \
    mwc_dropzone.h \
    core_messagebroker.h \
    log_nexuslogparser.h \
    log_abstractlogparser.h \
    core_productmanager.h \
    core_appinfo.h \
    test_componenttester.h \
    json_jsonparser.h \
    json_productrule.h \
    window_jsontestwidget.h \
    window_jsontextedit.h \
    mwc_menubar.h \
    window_windowmanager.h \
    mwc_progressdialog.h \
    window_aboutwidget.h \
    window_preferencewidget.h \
    core_preferencemanager.h \
    dao_preferencedataaccessor.h \
    dao_clvdataaccessor.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    readme.txt
