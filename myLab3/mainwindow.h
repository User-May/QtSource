#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

// 前置声明或直接包含头文件（二选一，推荐包含头文件）
#include "PatientWidget.h"
#include "DepartmentWidget.h"
#include "DoctorWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    PatientWidget* getPatientWidget() {
        return m_patientWidget;
    }

private:
    // 核心控件声明
    QStackedWidget *m_stackWidget;       // 堆叠窗口（切换界面）
    QPushButton *m_btnPatient;           // 管理患者按钮
    QPushButton *m_btnDept;              // 管理科室按钮
    QPushButton *m_btnDoctor;            // 管理医生按钮

    // 功能界面声明
    PatientWidget *m_patientWidget;      // 患者管理界面
    DepartmentWidget *m_deptWidget;      // 科室管理界面
    DoctorWidget *m_docWidget;           // 医生管理界面
};

#endif // MAINWINDOW_H
