#ifndef DOCTORMODEL_H
#define DOCTORMODEL_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "DBHelper.h"
#include "DepartmentModel.h"
#include "DataStruct.h"

class DoctorModel {
public:
    QList<Doctor> getAllDoctors();
    bool addDoctor(const Doctor& doc);
    bool updateDoctor(const Doctor& doc);
    bool deleteDoctor(const QString& docId);
    QString lastError() const { return m_lastError; }

private:
    QString m_lastError;
    // 根据科室ID获取名称
    QString getDeptName(const QString& deptId) {
        DepartmentModel deptModel;
        for (const auto& dept : deptModel.getAllDepartments()) {
            if (dept.id == deptId) return dept.name;
        }
        return "未知科室";
    }
};

#endif // DOCTORMODEL_H
