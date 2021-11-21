QT       += core gui

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
    Core/filesystem_handler.cpp \
    Core/playlist.cpp \
    Core/playlists_manager.cpp \
    Core/timer.cpp \
    Core/track_controller.cpp \
    main.cpp \
    UI/mainwindow.cpp \
    UI/stylehelper.cpp

HEADERS += \
    Core/core.h \
    Core/filesystem_handler.h \
    UI/mainwindow.h \
    UI/stylehelper.h\
    Core/music.h \
    Core/playlist.h \
    Core/playlists_manager.h \
    Core/timer.h \
    Core/track_controller.h

FORMS += \
    UI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    buttons/source.qrc \

DISTFILES += \
    buttons/130898.png \
    buttons/5ee00035459021.42522331.jpg \
    buttons/9dksh8DIjLA.jpg \
    buttons/X0Yb8fKRnDA.jpg \
    buttons/close-gray.png \
    buttons/close-orange.png \
    buttons/close.png \
    buttons/pause (2).png \
    buttons/pause-orange.png \
    buttons/pause.png \
    buttons/play (2).png \
    buttons/play-orange.png \
    buttons/play.png \
    buttons/plus (2).png \
    buttons/plus-orange.png \
    buttons/plus.png \
    buttons/shuffle.png \
    buttons/skip-next (2).png \
    buttons/skip-next-orange.png \
    buttons/skip-next.png \
    buttons/skip-previous (2).png \
    buttons/skip-previous-orange.png \
    buttons/skip-previous.png \
    buttons/stop (2).png \
    buttons/stop-orange.png \
    buttons/stop.png \
    buttons/window-maximize-gray.png \
    buttons/window-maximize.png \
    buttons/window-minimize-gray.png \
    buttons/window-minimize.png \
    buttons/window-restore-gray.png \
    buttons/window-restore.png
