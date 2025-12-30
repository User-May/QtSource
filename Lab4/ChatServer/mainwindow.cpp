#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkInterface>   // 用于获取网卡信息
#include <QHostAddress>       // IP地址类
#include <QStringList>        // 存储IP列表

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SeverLog->setReadOnly(true);

    m_chatServer=ChatServer::getInstance(this);
    this->AllIPAddress=getServerIPAddress();
    foreach(const QString& ip,AllIPAddress){
        if(ip=="10.62.97.210") m_chatServer->IPAddress=ip;
    }

    connect(m_chatServer,&ChatServer::sendLogMsg,this,&MainWindow::logMessege);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnControlServer_clicked()
{
    static bool isStarted=false;
    if(isStarted){
        ui->btnControlServer->setText("关闭服务器");
        m_chatServer->stopServer();
    }else{
        ui->btnControlServer->setText("启动服务器");
        m_chatServer->startServer(8888);
    }
    isStarted=!isStarted;
}

void MainWindow::logMessege(const QString &s)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStr = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    ui->SeverLog->appendPlainText(timeStr+": "+s);
}

QStringList MainWindow::getServerIPAddress()
{
    QStringList ipList; // 存储所有可用IP
    QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();
    for(const QHostAddress &addr:allAddresses){
        if(addr.protocol()==QAbstractSocket::IPv4Protocol && !addr.isLoopback()){
            ipList.append(addr.toString());
        }
    }
    return ipList;
}

