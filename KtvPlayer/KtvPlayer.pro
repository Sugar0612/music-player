QT       += core gui multimedia
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/LoginWidget/loginw.cpp \
    Control/LoginWidget/register.cpp \
    Control/LrcWidget/Lrcwgt.cpp \
    Control/NewButton.cpp \
    Control/Newlistwidget.cpp \
    Control/PlayListWidget/PlayList.cpp \
    Control/SongListWidget/SongListWidget.cpp \
    Control/newlable.cpp \
    Control/newtablewidget.cpp \
    Module/MusicPlayer/MusicPlayer.cpp \
    Module/Network/network.cpp \
    Module/Sql/Sql.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Control/LoginWidget/loginw.h \
    Control/LoginWidget/register.h \
    Control/LrcWidget/Lrcwgt.h \
    Control/NewButton.h \
    Control/Newlistwidget.h \
    Control/PlayListWidget/PlayList.h \
    Control/SongListWidget/SongListWidget.h \
    Control/newlable.h \
    Control/newtablewidget.h \
    Module/MusicPlayer/MusicPlayer.h \
    Module/Network/network.h \
    Module/Sql/Sql.h \
    Tool/MD5.h \
    Tool/MusicStruct.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Texture.qrc
