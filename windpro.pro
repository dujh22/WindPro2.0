QT += core gui
QT += charts
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = windpro
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    conditionwidget.cpp \
    global.cpp \
    leftdownwidget.cpp \
    lefttopwidget.cpp \
    measuresetwidget.cpp \
    parameterswidget.cpp \
    pickwidget.cpp \
    rightdownwidget.cpp \
    righttopwidget.cpp \
    tablewidget.cpp \
    updatewidget.cpp \
    qwchartview.cpp \ 
    subpaint.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    conditionwidget.h \
    global.h \
    leftdownwidget.h \
    lefttopwidget.h \
    measuresetwidget.h \
    parameterswidget.h \
    pickwidget.h \
    rightdownwidget.h \
    righttopwidget.h \
    tablewidget.h \
    updatewidget.h \
    qwchartview.h \
    subpaint.h \
    qwchartview.h \
    qcustomplot.h

RESOURCES += \
    source.qrc

RC_FILE += qtdemo.rc

