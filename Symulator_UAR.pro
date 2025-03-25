QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arx_model.cpp \
    dialog.cpp \
    filemanager.cpp \
    generator.cpp \
    io.cpp \
    loopsystem.cpp \
    main.cpp \
    gui.cpp \
    pid_regulator.cpp \
    simulation.cpp

HEADERS += \
    SignalType.h \
    arx_model.h \
    dialog.h \
    filemanager.h \
    generator.h \
    gui.h \
    io.h \
    loopsystem.h \
    pid_regulator.h \
    simulation.h

FORMS += \
    dialog.ui \
    gui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
