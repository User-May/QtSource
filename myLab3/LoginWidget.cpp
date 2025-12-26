#include "LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    // 界面布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("用户名："));
    m_usernameEdit = new QLineEdit();
    layout->addWidget(m_usernameEdit);

    layout->addWidget(new QLabel("密码："));
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(m_passwordEdit);

    m_loginBtn = new QPushButton("登录");
    layout->addWidget(m_loginBtn);

    connect(m_loginBtn, &QPushButton::clicked, this, &LoginWidget::onLoginBtnClicked);
}

void LoginWidget::onLoginBtnClicked() {
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text().trimmed();
    if (!username.isEmpty() && !password.isEmpty()) {
        emit loginRequested(username, password);
    }
}
