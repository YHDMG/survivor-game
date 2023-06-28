QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    button.cpp \
    enemy.cpp \
    gamescene.cpp \
    hero.cpp \
    loot.cpp \
    main.cpp \
    mainscene.cpp \
    preparescene.cpp \
    strengthenscene.cpp

HEADERS += \
    bullet.h \
    button.h \
    enemy.h \
    gamescene.h \
    hero.h \
    loot.h \
    mainscene.h \
    preparescene.h \
    strengthenscene.h

FORMS += \
    mainscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
