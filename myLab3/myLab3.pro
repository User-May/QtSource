QT       += core gui
QT += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddPatientDialog.cpp \
    DBHelper.cpp \
    DepartmentModel.cpp \
    DepartmentWidget.cpp \
    DoctorModel.cpp \
    DoctorWidget.cpp \
    LoginController.cpp \
    LoginWidget.cpp \
    PatientController.cpp \
    PatientModel.cpp \
    PatientWidget.cpp \
    UserModel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddPatientDialog.h \
    DBHelper.h \
    DataStruct.h \
    DepartmentModel.h \
    DepartmentWidget.h \
    DoctorModel.h \
    DoctorWidget.h \
    LoginController.h \
    LoginWidget.h \
    PatientController.h \
    PatientModel.h \
    PatientWidget.h \
    UserModel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
