#include "DBHelper.h"
#include <QDebug>
#include <QSqlError>

DBHelper* DBHelper::m_instance = nullptr;

DBHelper::DBHelper() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("D:/Qt/mySource/myLab3/Lab3.db");
    if (!m_db.open()) {
        qDebug() << "数据库连接失败：" << m_db.lastError().text();
    } else {
        qDebug() << "成功连接数据库：" << m_db.databaseName();
    }
}

DBHelper::~DBHelper() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

DBHelper* DBHelper::getInstance() {
    if (!m_instance) {
        m_instance = new DBHelper();
    }
    return m_instance;
}

QSqlDatabase DBHelper::getDB() {
    return m_db;
}
