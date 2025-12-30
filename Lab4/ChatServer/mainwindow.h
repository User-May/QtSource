#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"chatserver.h"
#include <QMainWindow>
#include <QDateTime>
#include <QTcpSocket>


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
    void on_btnControlServer_clicked();
    void logMessege(const QString& s);

private:
    Ui::MainWindow *ui;
    QString IPAddress;
    ChatServer *m_chatServer;
    const QString Port="8888";
    QStringList AllIPAddress;
    QStringList getServerIPAddress();
};
#endif // MAINWINDOW_H
