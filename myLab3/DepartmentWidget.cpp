#include "DepartmentWidget.h"
#include "DepartmentModel.h"

DepartmentWidget::DepartmentWidget(QWidget *parent) : QWidget(parent) {
    m_model = new DepartmentModel();

    // 表格初始化
    m_table = new QTableWidget(this);
    m_table->setColumnCount(2);
    m_table->setHorizontalHeaderLabels({"科室ID", "科室名称"});
    m_table->horizontalHeader()->setStretchLastSection(true);

    // 输入框+按钮
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("输入科室名称");
    m_addBtn = new QPushButton("添加科室");
    m_updateBtn = new QPushButton("修改科室");
    m_deleteBtn = new QPushButton("删除科室");

    // 布局
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(m_nameEdit);
    inputLayout->addWidget(m_addBtn);
    inputLayout->addWidget(m_updateBtn);
    inputLayout->addWidget(m_deleteBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_table);
    setLayout(mainLayout);

    // 信号绑定
    connect(m_addBtn, &QPushButton::clicked, this, &DepartmentWidget::onAddBtnClicked);
    connect(m_updateBtn, &QPushButton::clicked, this, &DepartmentWidget::onUpdateBtnClicked);
    connect(m_deleteBtn, &QPushButton::clicked, this, &DepartmentWidget::onDeleteBtnClicked);

    // 初始化加载科室数据
    refreshTable(m_model->getAllDepartments());
}

void DepartmentWidget::refreshTable(const QList<Department>& depts) {
    m_table->setRowCount(0);
    for (int i = 0; i < depts.size(); ++i) {
        m_table->insertRow(i);
        m_table->setItem(i, 0, new QTableWidgetItem(depts[i].id));
        m_table->setItem(i, 1, new QTableWidgetItem(depts[i].name));
    }
}

void DepartmentWidget::onAddBtnClicked() {
    QString name = m_nameEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入科室名称");
        return;
    }
    Department dept{ "", name };
    if (m_model->addDepartment(dept)) {
        QMessageBox::information(this, "成功", "科室添加完成");
        m_nameEdit->clear();
        refreshTable(m_model->getAllDepartments());
    } else {
        QMessageBox::critical(this, "失败", "添加失败：" + m_model->lastError());
    }
}

void DepartmentWidget::onUpdateBtnClicked() {
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要修改的科室");
        return;
    }
    Department dept;
    dept.id = m_table->item(row, 0)->text();
    dept.name = m_nameEdit->text().trimmed();
    if (dept.name.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入新名称");
        return;
    }
    if (m_model->updateDepartment(dept)) {
        QMessageBox::information(this, "成功", "科室修改完成");
        refreshTable(m_model->getAllDepartments());
    } else {
        QMessageBox::critical(this, "失败", "修改失败：" + m_model->lastError());
    }
}

void DepartmentWidget::onDeleteBtnClicked() {
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要删除的科室");
        return;
    }
    if (QMessageBox::question(this, "确认", "是否删除该科室？") != QMessageBox::Yes) return;

    QString deptId = m_table->item(row, 0)->text();
    if (m_model->deleteDepartment(deptId)) {
        QMessageBox::information(this, "成功", "科室删除完成");
        refreshTable(m_model->getAllDepartments());
    } else {
        QMessageBox::critical(this, "失败", "删除失败：" + m_model->lastError());
    }
}
