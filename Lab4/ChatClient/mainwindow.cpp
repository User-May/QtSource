#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->PageLogin);
    ui->MessageArea->setReadOnly(true);
    m_socket=new QTcpSocket(this);

    connect(m_socket,&QTcpSocket::connected,this,&MainWindow::onConnected);
    connect(m_socket,&QTcpSocket::errorOccurred,this,&MainWindow::onConnectError);
    connect(m_socket,&QTcpSocket::readyRead,this,&MainWindow::onServerDataReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnLogin_clicked()
{
    this->nickname=ui->NickName->text();
    QString serverIP=ui->IPAddress->text();

    if (m_socket->state() != QTcpSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
    }
    m_socket->connectToHost(QHostAddress(serverIP), serverPort);
}


void MainWindow::on_btnLogout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->PageLogin);
}


void MainWindow::on_btnSendMessege_clicked()
{
    if (m_socket->state() != QTcpSocket::ConnectedState){
        QMessageBox::critical(nullptr, "发送错误", "还没有与服务器端建立链接！");
        return;
    }
    QString msg=ui->Message->text();
    ui->Message->clear();
    if(msg.isEmpty()) return;

    QJsonObject msgJson;
    msgJson["NewMessage"]=true;
    msgJson["sender"]=this->nickname;
    msgJson["content"]=msg;
    msgJson["time"]=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QJsonDocument doc(msgJson);
    QByteArray sendData = doc.toJson(QJsonDocument::Compact);

    qint64 sendLen = m_socket->write(sendData);
    if(sendLen==-1){
        QMessageBox::critical(nullptr, "发送错误", "发送消失失败！");
    }else{
        addMessage(nickname,msg,true);
    }
}

void MainWindow::onConnected()
{
    QJsonObject msgJson;
    msgJson["NewMessage"]=false;
    msgJson["sender"]=this->nickname;
    msgJson["time"]=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    QJsonDocument doc(msgJson);
    QByteArray sendData = doc.toJson(QJsonDocument::Compact);
    qint64 sendLen = m_socket->write(sendData);
    if(sendLen==-1){
        QMessageBox::critical(nullptr, "发送错误", "发送初始消息失败！");
    }
    qDebug()<<"连接到服务器端成功！";
    ui->stackedWidget->setCurrentWidget(ui->PageChat);
}

void MainWindow::onConnectError()
{
    QMessageBox::critical(nullptr, "连接错误", m_socket->errorString());
}

void MainWindow::onServerDataReceived()
{
    qDebug()<<"正在处理服务器发过来的数据";
    QByteArray recvData=m_socket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(recvData);
    if (jsonDoc.isObject()) {
        QJsonObject msgJson = jsonDoc.object();
        if(!msgJson["NewMessage"].toBool()){
            QJsonArray users=msgJson["users"].toArray();
            this->m_userList.clear();
            for(const QJsonValue& user:users){
                qDebug()<<user.toString();
                m_userList.insert(user.toString());
            }
            this->updateUserList();
        }else{
            QString sender = msgJson["sender"].toString(); // 发送者昵称
            QString content = msgJson["content"].toString(); // 消息内容
            QString time = msgJson["time"].toString(); // 发送时间
            qDebug()<<sender;
            addMessage(sender+" 于"+time+":",content,false);
        }
    } else {
        QMessageBox::critical(nullptr, "解析数据错误", "收到无效的Json数据！");
    }
}

void MainWindow::addMessage(const QString &sender, const QString &message, bool isSelf)
{
    QTextCursor cursor = ui->MessageArea->textCursor();
    cursor.movePosition(QTextCursor::End);

    // 添加消息间的间隔
    if (!ui->MessageArea->document()->isEmpty()) {
        cursor.insertBlock();
    }

    // 第一行：发送者名字
    QTextBlockFormat nameBlockFormat;
    nameBlockFormat.setAlignment(isSelf ? Qt::AlignRight : Qt::AlignLeft);
    // nameBlockFormat.setLeftMargin(isSelf ? 0 : 30);
    // nameBlockFormat.setRightMargin(isSelf ? 30 : 0);

    cursor.setBlockFormat(nameBlockFormat);

    QTextCharFormat nameFormat;
    nameFormat.setFontWeight(QFont::Bold);
    if(isSelf) nameFormat.setForeground(Qt::darkGreen);


    cursor.insertText(isSelf ? "我" : sender, nameFormat);
    cursor.insertBlock();  // 换行到下一行

    // 第二行：消息内容
    QTextBlockFormat msgBlockFormat;
    msgBlockFormat.setAlignment(isSelf ? Qt::AlignRight : Qt::AlignLeft);
    msgBlockFormat.setLeftMargin(isSelf ? 100 : 40);    // 消息缩进更多
    msgBlockFormat.setRightMargin(isSelf ? 40 : 100);
    msgBlockFormat.setTopMargin(2);
    msgBlockFormat.setBottomMargin(2);

    cursor.setBlockFormat(msgBlockFormat);

    // 简单插入消息内容
    cursor.insertText(message);

    // 添加一个空行作为消息间的间隔
    cursor.insertBlock();

    // 确保光标可见
    ui->MessageArea->setTextCursor(cursor);
    ui->MessageArea->ensureCursorVisible();
}

void MainWindow::updateUserList()
{
    ui->UserList->clear();
    for(const QString& user:m_userList){
        ui->UserList->addItem(user);
    }
}

