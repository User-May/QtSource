#include "LoginController.h"
#include "PatientModel.h" // 新增：包含PatientModel头文件
#include "PatientWidget.h" // 新增：包含PatientWidget头文件
#include <QMessageBox>

LoginController::LoginController(LoginWidget* view, UserModel* model) : QObject(nullptr) {
    m_view = view;
    m_model = model;
    m_mainWindow = new MainWindow();

    connect(m_view, &LoginWidget::loginRequested, this, &LoginController::onLoginRequested);
}

void LoginController::onLoginRequested(const QString& username, const QString& password) {
    if (m_model->checkLogin(username, password)) {
        m_view->hide();
        m_mainWindow->show();

        // 登录成功后，强制刷新患者列表（核心兜底逻辑）
        PatientModel patientModel;
        PatientWidget* patientWidget = m_mainWindow->getPatientWidget();
        if (patientWidget) {
            QList<Patient> allPatients = patientModel.getAllPatients();
            patientWidget->refreshPatientTable(allPatients);
            qDebug() << "登录成功，刷新患者列表，数量：" << allPatients.size();
        } else {
            qDebug() << "登录成功，但PatientWidget为空！";
        }
    } else {
        QMessageBox::critical(m_view, "错误", "用户名或密码错误！");
    }
}
