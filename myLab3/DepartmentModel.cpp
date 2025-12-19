#include "DepartmentModel.h"
#include <QSqlError>

QList<Department> DepartmentModel::getAllDepartments() {
    QList<Department> depts;
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return depts;
    }
    QSqlQuery query("SELECT ID, NAME FROM Department", db);
    while (query.next()) {
        depts.append({ query.value(0).toString(), query.value(1).toString() });
    }
    m_lastError = query.lastError().text();
    return depts;
}

bool DepartmentModel::addDepartment(const Department& dept) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        qDebug() << "[添加科室] 数据库未连接"; // 新增调试
        return false;
    }

    // 新增：打印要插入的科室名称（检查是否为空）
    qDebug() << "[添加科室] 要插入的名称：" << dept.name;

    QSqlQuery query(db);
    query.prepare("INSERT INTO Department (NAME) VALUES (?)");
    query.addBindValue(dept.name);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        // 新增：打印完整错误信息
        qDebug() << "[添加科室失败] 错误详情：" << m_lastError;
        return false;
    }

    // 新增：打印插入成功的ID（验证自增）
    qDebug() << "[添加科室成功] 自动生成的ID：" << query.lastInsertId().toInt();
    return true;
}

bool DepartmentModel::updateDepartment(const Department& dept) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE Department SET NAME=? WHERE ID=?");
    query.addBindValue(dept.name);
    query.addBindValue(dept.id);
    if (!query.exec() || query.numRowsAffected() == 0) {
        m_lastError = query.lastError().text().isEmpty() ? "未找到该科室" : query.lastError().text();
        return false;
    }
    return true;
}

bool DepartmentModel::deleteDepartment(const QString& deptId) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return false;
    }
    // 检查是否有关联医生（外键约束）
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM Doctor WHERE DEPARTMENT_ID=?");
    checkQuery.addBindValue(deptId);
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        m_lastError = "该科室关联了医生，无法删除";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("DELETE FROM Department WHERE ID=?");
    query.addBindValue(deptId);
    if (!query.exec() || query.numRowsAffected() == 0) {
        m_lastError = query.lastError().text().isEmpty() ? "未找到该科室" : query.lastError().text();
        return false;
    }
    return true;
}
