#ifndef DOCTORWIDGET_H
#define DOCTORWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include "DataStruct.h"


class DoctorModel;
class DepartmentModel;

class DoctorWidget : public QWidget {
    Q_OBJECT
public:
    explicit DoctorWidget(QWidget *parent = nullptr);
private slots:
    void onAddBtnClicked();
    void onUpdateBtnClicked();
    void onDeleteBtnClicked();
    void refreshTable(const QList<Doctor>& docs);
    void refreshDeptCombo(); // 刷新科室下拉框
private:
    QTableWidget *m_table;
    QLineEdit *m_empNoEdit, *m_nameEdit;
    QComboBox *m_deptCombo;
    QPushButton *m_addBtn, *m_updateBtn, *m_deleteBtn;
    DoctorModel *m_docModel;
    DepartmentModel *m_deptModel;
};

#endif // DOCTORWIDGET_H
