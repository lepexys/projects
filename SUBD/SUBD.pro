QT       += core gui sql printsupport

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
    add_del.cpp \
    add_sal.cpp \
    bill.cpp \
    clients.cpp \
    dealers.cpp \
    deliveries.cpp \
    goods.cpp \
    main.cpp \
    mainwindow.cpp \
    print.cpp \
    sales.cpp \
    storage.cpp

HEADERS += \
    add_del.h \
    add_sal.h \
    bill.h \
    clients.h \
    dealers.h \
    deliveries.h \
    goods.h \
    mainwindow.h \
    print.h \
    sales.h \
    storage.h

FORMS += \
    add_del.ui \
    add_sal.ui \
    bill.ui \
    clients.ui \
    dealers.ui \
    deliveries.ui \
    goods.ui \
    mainwindow.ui \
    print.ui \
    sales.ui \
    storage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
