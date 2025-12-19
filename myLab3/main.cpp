#include <QApplication>
#include "LoginWidget.h"
#include "UserModel.h"
#include "LoginController.h"
#include "MainWindow.h"
#include "PatientModel.h"
#include "PatientController.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 1. 登录模块（正确）
    LoginWidget loginWidget;
    UserModel userModel;
    LoginController loginController(&loginWidget, &userModel);

    // 显示登录界面
    loginWidget.show();

    return a.exec();//
}
