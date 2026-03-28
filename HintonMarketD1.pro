QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../BusinessLicence.cpp \
    ../ComplianceDocumentation.cpp \
    ../DashboardControl.cpp \
    ../LiabilityInsurance.cpp \
    ../MarketOperator.cpp \
    ../MarketStall.cpp \
    ../OFHC.cpp \
    ../SystemAdministrator.cpp \
    ../User.cpp \
    ../Vendor.cpp \
    ../Waitlist.cpp \
    AccountStorage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../BusinessLicence.h \
    ../ComplianceDocumentation.h \
    ../DashboardControl.h \
    ../LiabilityInsurance.h \
    ../MarketOperator.h \
    ../MarketStall.h \
    ../OFHC.h \
    ../SystemAdministrator.h \
    ../User.h \
    ../Vendor.h \
    ../Waitlist.h \
    AccountStorage.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
