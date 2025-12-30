#include "chatserver.h"

ChatServer* ChatServer::m_ChatServer=nullptr;

ChatServer::ChatServer(QObject *parent):QTcpServer(parent)
{
    ClientSockets.clear();
}

ChatServer *ChatServer::getInstance(QObject *parent)
{
    if(m_ChatServer==nullptr){
        m_ChatServer=new ChatServer(parent);
    }
    return m_ChatServer;
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    emit sendLogMsg("新的客户端尝试建立连接...");
    QTcpSocket *clientSocket=new QTcpSocket(this);
    if(!clientSocket->setSocketDescriptor(socketDescriptor)){
        clientSocket->deleteLater();
        emit sendLogMsg("客户端绑定套接字失败！");
        return;
    }

    foreach(QTcpSocket* client,ClientSockets){
        if(client==clientSocket){
            emit sendLogMsg("相同的客户端进行链接！");
        }
    }
    ClientSockets.append(clientSocket);
    QString clientIp = clientSocket->peerAddress().toString();
    quint16 clientPort=clientSocket->peerPort();
    QString connectLog = QString("与新客户端连接成功,客户端IP：%1,客户端端口：%2,目前客户端个数：%3").arg(clientIp).arg(clientPort).arg(ClientSockets.size());
    emit sendLogMsg(connectLog);

    connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
        this->readClientData(clientSocket);
    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        ClientSockets.removeOne(clientSocket);
        QString disconnectLog = QString("客户端%1断开连接!").arg(clientIp);
        this->m_userList.remove(clientSocket);
        QJsonObject JsonData;
        QJsonArray userList;
        for(const auto &[Cs,name]:m_userList.asKeyValueRange()){
            userList.append(name);
        }
        JsonData["NewMessage"]=false;
        JsonData["users"]=userList;
        QJsonDocument JsonDoc(JsonData);
        this->broadcastMsg(JsonDoc.toJson(QJsonDocument::Compact),nullptr);
        emit sendLogMsg(disconnectLog);
        clientSocket->deleteLater();
    });
}

void ChatServer::startServer(quint16 m_Port)
{
    QString msg;
    if(this->listen(QHostAddress::Any,m_Port)){
        msg=QString("服务器启动成功！聊天室IP地址为：")+IPAddress+"   正在监听端口："+QString::number(m_Port);
    }else{
        msg="服务器启动失败：监听端口失败:"+this->errorString();
    }
    emit sendLogMsg(msg);
}

void ChatServer::stopServer()
{
    close();

    for(QTcpSocket* socket : ClientSockets){
        socket->disconnectFromHost();
        socket->deleteLater();
    }
    ClientSockets.clear();
    QString msg="服务器停止，已断开与所有用户的链接!";
    emit sendLogMsg(msg);
}

void ChatServer::readClientData(QTcpSocket *clientSocket)
{
    QByteArray receiveData=clientSocket->readAll();
    if(receiveData.isEmpty()) return;

    QJsonDocument JsonDoc=QJsonDocument::fromJson(receiveData);
    if(JsonDoc.isObject()){
        QJsonObject msgJson = JsonDoc.object();
        QString sender = msgJson["sender"].toString(); // 发送者昵称
        if(!msgJson["NewMessage"].toBool()){
            qDebug()<<"新用户到来，准备更新！";
            m_userList[clientSocket]=sender;
            QJsonArray userList;
            for(const auto &[Cs,name]:m_userList.asKeyValueRange()){
                userList.append(name);
            }
            msgJson["users"]=userList;
            QJsonDocument doc(msgJson);
            receiveData=doc.toJson(QJsonDocument::Compact);
            this->broadcastMsg(receiveData,nullptr);
        }else{
            QString content = msgJson["content"].toString(); // 消息内容
            QString time = msgJson["time"].toString(); // 发送时间
            QString jsonLog = QString("收到%1（%2）的消息：%3").arg(clientSocket->peerAddress().toString(), sender, content);
            emit sendLogMsg(jsonLog);
            this->broadcastMsg(receiveData, clientSocket);
        }
    }else{
        QString errorLog = QString("收到%1的无效JSON数据").arg(clientSocket->peerAddress().toString());
        emit sendLogMsg(errorLog);
    }
}

void ChatServer::broadcastMsg(QByteArray msgData, QTcpSocket *sender)
{
    foreach(QTcpSocket* client,ClientSockets){
        if(client!=sender && client->state()==QTcpSocket::ConnectedState){
            client->write(msgData);
        }
    }
}





