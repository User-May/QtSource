#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <QString>

// 科室结构体
struct Department {
    QString id;
    QString name;
};

// 医生结构体
struct Doctor {
    QString id;
    QString employeeNo;
    QString name;
    QString departmentId;
    QString departmentName; // 显示用
};


#endif // DATASTRUCT_H
