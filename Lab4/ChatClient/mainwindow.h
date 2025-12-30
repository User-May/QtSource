#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QSet>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();
    void on_btnSendMessege_clicked();
    void onConnected();
    void onConnectError();
    void onServerDataReceived();
private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
    QString nickname="未命名用户";
    quint16 serverPort=8888;
    QSet<QString> m_userList;
    void addMessage(const QString& sender, const QString& message, bool isSelf);
    void updateUserList();
};
#endif // MAINWINDOW_H
