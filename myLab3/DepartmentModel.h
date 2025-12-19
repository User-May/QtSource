#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "DBHelper.h"
#include "DataStruct.h"


class DepartmentModel {
public:
    QList<Department> getAllDepartments(); // 获取所有科室
    bool addDepartment(const Department& dept); // 添加科室
    bool updateDepartment(const Department& dept); // 修改科室
    bool deleteDepartment(const QString& deptId); // 删除科室
    QString lastError() const { return m_lastError; } // 错误信息

private:
    QString m_lastError;
};

#endif // DEPARTMENTMODEL_H
