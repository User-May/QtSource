#ifndef DEPARTMENTWIDGET_H
#define DEPARTMENTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include "DataStruct.h"

class DepartmentModel; // 前置声明

class DepartmentWidget : public QWidget {
    Q_OBJECT
public:
    explicit DepartmentWidget(QWidget *parent = nullptr);
private slots:
    void onAddBtnClicked();   // 添加科室
    void onUpdateBtnClicked();// 修改科室
    void onDeleteBtnClicked();// 删除科室
    void refreshTable(const QList<Department>& depts); // 刷新表格
private:
    QTableWidget *m_table;
    QLineEdit *m_nameEdit;
    QPushButton *m_addBtn, *m_updateBtn, *m_deleteBtn;
    DepartmentModel *m_model;
};

#endif // DEPARTMENTWIDGET_H
