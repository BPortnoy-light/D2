QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BookingRequest.cpp \
    BusinessLicence.cpp \
    ComplianceDocumentation.cpp \
    DashboardControl.cpp \
    DatabaseManager.cpp \
    LiabilityInsurance.cpp \
    MarketOperator.cpp \
    MarketSchedule.cpp \
    MarketStall.cpp \
    MarketWeek.cpp \
    Notification.cpp \
    NotificationStorage.cpp \
    OFHC.cpp \
    Request.cpp \
    StorageRequest.cpp \
    SystemAdministrator.cpp \
    User.cpp \
    Vendor.cpp \
    ViewRequest.cpp \
    Waitlist.cpp \
    AccountStorage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BookingRequest.h \
    BusinessLicence.h \
    ComplianceDocumentation.h \
    DashboardControl.h \
    DatabaseManager.h \
    LiabilityInsurance.h \
    MarketOperator.h \
    MarketSchedule.h \
    MarketStall.h \
    MarketWeek.h \
    Notification.h \
    NotificationStorage.h \
    OFHC.h \
    Request.h \
    StorageRequest.h \
    SystemAdministrator.h \
    User.h \
    Vendor.h \
    ViewRequest.h \
    Waitlist.h \
    AccountStorage.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

copydb.commands = test -f $$OUT_PWD/inventory.db || cp $$PWD/inventory.db $$OUT_PWD/ QMAKE_EXTRA_TARGETS += copydb PRE_TARGETDEPS += copydb

DISTFILES +=
