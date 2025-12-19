#include "PatientModel.h"
#include "DBHelper.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

QList<Patient> PatientModel::getAllPatients() {
    QList<Patient> patients;
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) return patients;

    QSqlQuery query("SELECT * FROM Patient", db);
    while (query.next()) {
        Patient p;
        p.id = query.value("ID").toString();
        p.idCard = query.value("ID_CARD").toString();
        p.name = query.value("NAME").toString();
        p.sex = query.value("SEX").toInt();
        p.dob = query.value("DOB").toString();
        p.height = query.value("HEIGHT").toDouble();
        p.weight = query.value("WEIGHT").toDouble();
        p.mobile = query.value("MOBILEPHONE").toString();
        p.age = query.value("AGE").toInt();
        p.createdTimestamp = query.value("CREATEDTIMESTAMP").toString();
        patients.append(p);
    }
    return patients;
}

QList<Patient> PatientModel::searchPatientByName(const QString& name) {
    QList<Patient> patients;
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        qDebug() << "查询失败：数据库未打开";
        return patients;
    }

    QSqlQuery query(db);
    QString searchKey = "%" + name.trimmed() + "%";
    query.prepare("SELECT * FROM Patient WHERE NAME LIKE ?");
    query.addBindValue(searchKey);

    // 新增：打印完整的SQL和绑定值（复制此SQL到Navicat执行，验证是否有结果）
    qDebug() << "待执行SQL：" << query.executedQuery(); // 打印最终执行的SQL
    qDebug() << "绑定的搜索值：" << searchKey;

    if (!query.exec()) {
        qDebug() << "查询SQL执行失败：" << query.lastError().text();
        return patients;
    }

    // 新增：打印查询结果总数（关键！若总数=全量患者数，说明WHERE条件无效）
    int count = 0;
    while (query.next()) {
        count++;
        Patient p;
        p.id = query.value("ID").toString();
        p.idCard = query.value("ID_CARD").toString();
        p.name = query.value("NAME").toString();
        p.sex = query.value("SEX").toInt();
        p.dob = query.value("DOB").toString();
        p.height = query.value("HEIGHT").toDouble();
        p.weight = query.value("WEIGHT").toDouble();
        p.mobile = query.value("MOBILEPHONE").toString();
        p.age = query.value("AGE").toInt();
        p.createdTimestamp = query.value("CREATEDTIMESTAMP").toString();
        patients.append(p);
    }
    qDebug() << "查询返回数量：" << count << " | 全量患者数量：" << getAllPatients().size();

    return patients;
}

bool PatientModel::addPatient(const Patient& patient) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        qDebug() << "添加失败：数据库未打开";
        return false;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO Patient (ID, ID_CARD, NAME, SEX, DOB, HEIGHT, WEIGHT, MOBILEPHONE, AGE, CREATEDTIMESTAMP)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");
    query.addBindValue(patient.id);
    query.addBindValue(patient.idCard);
    query.addBindValue(patient.name);
    query.addBindValue(patient.sex);
    query.addBindValue(patient.dob);
    query.addBindValue(patient.height);
    query.addBindValue(patient.weight);
    query.addBindValue(patient.mobile);
    query.addBindValue(patient.age);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    // 新增：打印SQL执行错误的具体信息
    if (!query.exec()) {
        qDebug() << "数据库插入失败：" << query.lastError().text();
        return false;
    }
    return true;
}

bool PatientModel::updatePatient(const Patient& patient) {
    // 1. 校验核心参数（ID不能为空且为有效数字）
    QString patientId = patient.id.trimmed();
    if (patientId.isEmpty() || !patientId.toInt()) {
        m_lastError = "修改失败：患者ID为空或无效";
        qDebug() << m_lastError;
        return false;
    }
    qDebug() << "【Model修改】目标ID：" << patientId;

    // 2. 数据库连接（使用绝对路径避免找不到）
    QSqlDatabase db;
    const QString connName = "PatientUpdate_" + patientId;
    if (QSqlDatabase::contains(connName)) {
        db = QSqlDatabase::database(connName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connName);
        // 替换为你的数据库绝对路径（例如：D:/Qt/mySource/myLab3/Lab3.db）
        db.setDatabaseName("D:/Qt/mySource/myLab3/Lab3.db");
    }

    if (!db.open()) {
        m_lastError = "数据库连接失败：" + db.lastError().text();
        qDebug() << m_lastError;
        QSqlDatabase::removeDatabase(connName);
        return false;
    }
    qDebug() << "【Model修改】数据库连接成功";

    // 3. 构造SQL（严格匹配表字段：NAME/ID_CARD/SEX/HEIGHT/WEIGHT/MOBILEPHONE/AGE/DOB）
    // 注意：不包含CREATEDTIMESTAMP（修改时不更新创建时间）
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE Patient
        SET
            NAME=?,          -- 1. 姓名
            ID_CARD=?,       -- 2. 身份证（表字段是ID_CARD）
            SEX=?,           -- 3. 性别
            HEIGHT=?,        -- 4. 身高
            WEIGHT=?,        -- 5. 体重
            MOBILEPHONE=?,   -- 6. 手机号（表字段是MOBILEPHONE，不是MOBILE）
            AGE=?,           -- 7. 年龄
            DOB=?            -- 8. 出生日期
        WHERE ID=?            -- 9. 目标ID（WHERE条件）
    )");

    // 4. 绑定参数（顺序与SQL占位符严格对应，共9个参数）
    query.addBindValue(patient.name);          // 1. 姓名
    query.addBindValue(patient.idCard);        // 2. 身份证
    query.addBindValue(patient.sex);           // 3. 性别
    query.addBindValue(patient.height);        // 4. 身高
    query.addBindValue(patient.weight);        // 5. 体重
    query.addBindValue(patient.mobile);        // 6. 手机号（Patient结构体中是mobile，对应表MOBILEPHONE）
    query.addBindValue(patient.age);           // 7. 年龄
    query.addBindValue(patient.dob);           // 8. 出生日期
    query.addBindValue(patientId);             // 9. 目标ID

    // 调试：验证参数数量
    qDebug() << "【Model修改】绑定参数数量：" << query.boundValues().size();

    // 5. 执行SQL
    if (!query.exec()) {
        m_lastError = "修改失败：" + query.lastError().text();
        qDebug() << m_lastError;
        db.close();
        QSqlDatabase::removeDatabase(connName);
        return false;
    }

    // 6. 验证修改结果
    int affectedRows = query.numRowsAffected();
    if (affectedRows == 0) {
        m_lastError = "修改失败：未找到ID为" + patientId + "的患者";
        qDebug() << m_lastError;
        db.close();
        QSqlDatabase::removeDatabase(connName);
        return false;
    }

    // 7. 成功逻辑
    m_lastError.clear();
    qDebug() << "修改成功：ID=" << patientId << "，影响行数=" << affectedRows;
    db.close();
    QSqlDatabase::removeDatabase(connName);
    return true;
}

bool PatientModel::deletePatient(const QString& patientId) {
    QSqlDatabase db = DBHelper::getInstance()->getDB();
    if (!db.isOpen()) {
        m_lastError = "数据库未连接";
        qDebug() << m_lastError;
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM Patient WHERE ID=?");
    query.addBindValue(patientId); // 绑定要删除的ID

    if (!query.exec()) {
        m_lastError = "删除失败：" + query.lastError().text();
        qDebug() << m_lastError;
        return false;
    }

    // 验证是否删除成功（影响行数=0说明ID不存在）
    int affectedRows = query.numRowsAffected();
    if (affectedRows == 0) {
        m_lastError = "删除失败：未找到ID为" + patientId + "的患者";
        qDebug() << m_lastError;
        return false;
    }

    m_lastError.clear();
    qDebug() << "删除成功：ID=" << patientId << "，影响行数=" << affectedRows;
    return true;
}

// 新增：实现lastError()函数
QString PatientModel::lastError() const {
    return m_lastError;
}
