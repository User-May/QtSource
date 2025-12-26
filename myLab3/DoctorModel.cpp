#include "DoctorModel.h"
#include <QSqlError>

QList<Doctor> DoctorModel::getAllDoctors() {
    QList<Doctor> docs;
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return docs;
    }
    QSqlQuery query("SELECT ID, EMPLOYEEENO, NAME, DEPARTMENT_ID FROM Doctor", db);
    while (query.next()) {
        Doctor doc;
        doc.id = query.value(0).toString();
        doc.employeeNo = query.value(1).toString();
        doc.name = query.value(2).toString();
        doc.departmentId = query.value(3).toString();
        doc.departmentName = getDeptName(doc.departmentId);
        docs.append(doc);
    }
    m_lastError = query.lastError().text();
    return docs;
}

bool DoctorModel::addDoctor(const Doctor& doc) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        qDebug() << "[添加医生] 数据库未连接";
        return false;
    }

    // 打印要插入的医生信息（调试用）
    qDebug() << "[添加医生] 工号：" << doc.employeeNo
             << " | 姓名：" << doc.name
             << " | 科室ID：" << doc.departmentId;

    QSqlQuery query(db);
    // SQL：插入3个字段（对应3个占位符）
    query.prepare("INSERT INTO Doctor (EMPLOYEEENO, NAME, DEPARTMENT_ID) VALUES (?, ?, ?)");
    // 绑定3个参数（与占位符数量一致）
    query.addBindValue(doc.employeeNo);  // 第1个参数：工号
    query.addBindValue(doc.name);        // 第2个参数：姓名
    query.addBindValue(doc.departmentId);// 第3个参数：科室ID

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "[添加医生失败] 错误详情：" << m_lastError;
        return false;
    }

    qDebug() << "[添加医生成功] 自动生成的ID：" << query.lastInsertId().toInt();
    return true;
}

bool DoctorModel::updateDoctor(const Doctor& doc) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("UPDATE Doctor SET EMPLOYEEENO=?, NAME=?, DEPARTMENT_ID=? WHERE ID=?");
    query.addBindValue(doc.employeeNo);
    query.addBindValue(doc.name);
    query.addBindValue(doc.departmentId);
    query.addBindValue(doc.id);
    if (!query.exec() || query.numRowsAffected() == 0) {
        m_lastError = query.lastError().text().isEmpty() ? "未找到该医生" : query.lastError().text();
        return false;
    }
    return true;
}

bool DoctorModel::deleteDoctor(const QString& docId) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        return false;
    }
    QSqlQuery query(db);
    query.prepare("DELETE FROM Doctor WHERE ID=?");
    query.addBindValue(docId);
    if (!query.exec() || query.numRowsAffected() == 0) {
        m_lastError = query.lastError().text().isEmpty() ? "未找到该医生" : query.lastError().text();
        return false;
    }
    return true;
}
