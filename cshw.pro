QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CCountry.cpp \
    CDisease.cpp \
    CPolicy.cpp \
    CWorld.cpp \
    csfunc.cpp \
    fhistoryscreen.cpp \
    MainWidget.cpp \
    dialog.cpp \
    game.cpp \
    main.cpp \
    pre.cpp \
    res.cpp \
    start.cpp

HEADERS += \
    PlagueSimulatorLib.hpp \
    fhistoryscreen.h \
    MainWidget.h \
    dialog.h \
    game.h \
    pre.h \
    res.h \
    start.h

FORMS += \
    fhistoryscreen.ui \
    dialog.ui \
    game.ui \
    pre.ui \
    res.ui \
    start.ui

TRANSLATIONS += \
    cshw_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc

DISTFILES += \
    ../source/countryInfo.txt
