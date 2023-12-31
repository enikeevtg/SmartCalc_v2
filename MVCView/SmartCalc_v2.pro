QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../MVCController/credit_controller.cc \
    ../MVCController/deposit_controller.cc \
    ../MVCController/smart_controller.cc \
    ../MVCModel/credit_calculator.cc \
    ../MVCModel/deposit_calculator.cc \
    ../MVCModel/expression_parser.cc \
    ../MVCModel/expression_solver.cc \
    ../MVCModel/smart_calculator.cc \
    creditcalcwindow.cc \
    depositcalcwindow.cc \
    main.cc \
    mainwindow.cc \
    qcustomplot.cc

HEADERS += \
    ../MVCController/credit_controller.h \
    ../MVCController/deposit_controller.h \
    ../MVCController/smart_controller.h \
    ../MVCModel/credit_calculator.h \
    ../MVCModel/deposit_calculator.h \
    ../MVCModel/expression_parser.h \
    ../MVCModel/expression_solver.h \
    ../MVCModel/smart_calculator.h \
    ../MVCModel/types.h \
    creditcalcwindow.h \
    depositcalcwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditcalcwindow.ui \
    depositcalcwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
