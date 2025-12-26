#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include "LoginWidget.h"
#include "UserModel.h"
#include "MainWindow.h"

class LoginController : public QObject {
    Q_OBJECT
public:
    explicit LoginController(LoginWidget* view, UserModel* model);
private slots:
    void onLoginRequested(const QString& username, const QString& password);
private:
    LoginWidget* m_view;
    UserModel* m_model;
    MainWindow* m_mainWindow;
};

#endif // LOGINCONTROLLER_H
