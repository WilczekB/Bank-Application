QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    accountmanager.h \
    accountswindow.h \
    bank.h \
    bankaccount.h \
    calculator.h \
    client.h \
    clientmanager.h \
    credit.h \
    creditcalculator.h \
    creditcalculatorwindow.h \
    creditschedule.h \
    emailsender.h \
    includes.h \
    interestcalculator.h \
    mycreditwindow.h \
    mydatawindow.h \
    newaccountwindow.h \
    registration.h \
    transaction.h \
    intransaction.h \
    login.h \
    mainwindow.h \
    outtransaction.h \
    payment.h \
    savingsaccount.h \
    statisticswindow.h \
    transactionwindow.h \
    witdrawalwindow.h

SOURCES += \
    accountmanager.cpp \
    accountswindow.cpp \
    bank.cpp \
    bankaccount.cpp \
    calculator.cpp \
    client.cpp \
    clientmanager.cpp \
    credit.cpp \
    creditcalculator.cpp \
    creditcalculatorwindow.cpp \
    creditschedule.cpp \
    emailsender.cpp \
    interestcalculator.cpp \
    mycreditwindow.cpp \
    mydatawindow.cpp \
    newaccountwindow.cpp \
    registration.cpp \
    transaction.cpp \
    intransaction.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    outtransaction.cpp \
    payment.cpp \
    savingsaccount.cpp \
    statisticswindow.cpp \
    transactionwindow.cpp \
    witdrawalwindow.cpp

FORMS += \
    accountswindow.ui \
    creditcalculatorwindow.ui \
    login.ui \
    mainwindow.ui \
    mycreditwindow.ui \
    mydatawindow.ui \
    newaccountwindow.ui \
    registration.ui \
    statisticswindow.ui \
    transactionwindow.ui \
    witdrawalwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

