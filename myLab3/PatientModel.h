#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H

#include <QString>
#include <QList>
#include <QSqlError>
#include <QDateTime>

struct Patient {
    QString id;
    QString idCard;
    QString name;
    int sex;
    QString dob;
    double height;
    double weight;
    QString mobile;
    int age;
    QString createdTimestamp;
};

class PatientModel {
public:
    QList<Patient> getAllPatients();
    QList<Patient> searchPatientByName(const QString& name);
    bool addPatient(const Patient& patient);
    bool updatePatient(const Patient& patient); // 修改函数
    bool deletePatient(const QString& patientId); // 删除函数
    QString lastError() const; // 错误信息

private:
    QString m_lastError; // 存储最后一次错误
};

#endif // PATIENTMODEL_H
