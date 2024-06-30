QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app

SOURCES += \
    CCountry.cpp \
    CDisease.cpp \
    CPolicy.cpp \
    CWorld.cpp \
    csfunc.cpp \
    fhistoryscreen.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    PlagueSimulatorLib.hpp \
    fhistoryscreen.h \
    mainwindow.h

FORMS += \
    fhistoryscreen.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    source/countryInfo.csv \
    source/diseaseInfo.csv \
    source/policyInfo.csv
