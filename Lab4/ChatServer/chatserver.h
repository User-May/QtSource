#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QObject>
#include<QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHash>
#include <QJsonArray>

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    QString IPAddress;
    static ChatServer* m_ChatServer;
    static ChatServer* getInstance(QObject *parent=nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
public slots:
    void startServer(quint16 m_Port=8888);
    void stopServer();
    void readClientData(QTcpSocket* clientSocket);
    void broadcastMsg(QByteArray msgData,QTcpSocket* sender);
signals:
    void sendLogMsg(QString msg);
private:
    QList<QTcpSocket*> ClientSockets;
    QHash<QTcpSocket*,QString> m_userList;
    ChatServer(QObject *parent=nullptr);
    ChatServer(const ChatServer&) = delete;
    ChatServer& operator=(const ChatServer&) = delete;
};

#endif // CHATSERVER_H
