#include "UserModel.h"
#include "DBHelper.h"
#include <QSqlQuery>
#include <QDebug>

bool UserModel::checkLogin(const QString& username, const QString& password) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        qDebug() << "登录失败：数据库未打开";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM User WHERE USERNAME = ? AND PASSWORD = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (query.exec() && query.next()) {
        qDebug() << "登录成功：找到用户" << username;
        return true;
    }
    qDebug() << "登录失败：无匹配用户";
    return false;
}

QString UserModel::getUserIdByUsername(const QString& username) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) return "";

    QSqlQuery query(db);
    query.prepare("SELECT ID FROM User WHERE USERNAME = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        return query.value("ID").toString();
    }
    return "";
}
