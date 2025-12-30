#include "serverworker.h"


ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
{
    this->m_serverSocket=new QTcpSocket(this);
}
