#include "DoctorWidget.h"
#include "DoctorModel.h"
#include "DepartmentModel.h"

DoctorWidget::DoctorWidget(QWidget *parent) : QWidget(parent) {
    m_docModel = new DoctorModel();
    m_deptModel = new DepartmentModel();

    // 表格初始化
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels({"医生ID", "工号", "姓名", "所属科室"});
    m_table->horizontalHeader()->setStretchLastSection(true);

    // 输入控件
    m_empNoEdit = new QLineEdit(this);
    m_empNoEdit->setPlaceholderText("输入医生工号");
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("输入医生姓名");
    m_deptCombo = new QComboBox(this);
    refreshDeptCombo();

    // 按钮
    m_addBtn = new QPushButton("添加医生");
    m_updateBtn = new QPushButton("修改医生");
    m_deleteBtn = new QPushButton("删除医生");

    // 布局
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(m_empNoEdit);
    inputLayout->addWidget(m_nameEdit);
    inputLayout->addWidget(m_deptCombo);
    inputLayout->addWidget(m_addBtn);
    inputLayout->addWidget(m_updateBtn);
    inputLayout->addWidget(m_deleteBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_table);
    setLayout(mainLayout);

    // 信号绑定
    connect(m_addBtn, &QPushButton::clicked, this, &DoctorWidget::onAddBtnClicked);
    connect(m_updateBtn, &QPushButton::clicked, this, &DoctorWidget::onUpdateBtnClicked);
    connect(m_deleteBtn, &QPushButton::clicked, this, &DoctorWidget::onDeleteBtnClicked);

    // 初始化加载医生数据
    refreshTable(m_docModel->getAllDoctors());
}

void DoctorWidget::refreshDeptCombo() {
    m_deptCombo->clear();
    QList<Department> depts = m_deptModel->getAllDepartments();
    for (const auto& dept : depts) {
        m_deptCombo->addItem(dept.name, dept.id); // 显示名称，存储ID
    }
}

void DoctorWidget::refreshTable(const QList<Doctor>& docs) {
    m_table->setRowCount(0);
    for (int i = 0; i < docs.size(); ++i) {
        m_table->insertRow(i);
        m_table->setItem(i, 0, new QTableWidgetItem(docs[i].id));
        m_table->setItem(i, 1, new QTableWidgetItem(docs[i].employeeNo));
        m_table->setItem(i, 2, new QTableWidgetItem(docs[i].name));
        m_table->setItem(i, 3, new QTableWidgetItem(docs[i].departmentName));
    }
}

void DoctorWidget::onAddBtnClicked() {
    QString empNo = m_empNoEdit->text().trimmed();
    QString name = m_nameEdit->text().trimmed();
    if (empNo.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写工号和姓名！");
        return;
    }
    if (m_deptCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "提示", "请选择所属科室！");
        return;
    }

    // 构造Doctor对象（包含工号、姓名、科室ID）
    Doctor doc;
    doc.employeeNo = empNo;
    doc.name = name;
    doc.departmentId = m_deptCombo->currentData().toString(); // 确保科室ID非空

    if (m_docModel->addDoctor(doc)) {
        QMessageBox::information(this, "成功", "医生添加完成");
        m_empNoEdit->clear();
        m_nameEdit->clear();
        refreshTable(m_docModel->getAllDoctors());
    } else {
        QMessageBox::critical(this, "失败", "添加失败：" + m_docModel->lastError());
    }
}

void DoctorWidget::onUpdateBtnClicked() {
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要修改的医生");
        return;
    }
    Doctor doc;
    doc.id = m_table->item(row, 0)->text();
    doc.employeeNo = m_empNoEdit->text().trimmed();
    doc.name = m_nameEdit->text().trimmed();
    if (doc.employeeNo.isEmpty() || doc.name.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写工号和姓名");
        return;
    }
    doc.departmentId = m_deptCombo->currentData().toString();
    if (m_docModel->updateDoctor(doc)) {
        QMessageBox::information(this, "成功", "医生修改完成");
        refreshTable(m_docModel->getAllDoctors());
    } else {
        QMessageBox::critical(this, "失败", "修改失败：" + m_docModel->lastError());
    }
}

void DoctorWidget::onDeleteBtnClicked() {
    int row = m_table->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要删除的医生");
        return;
    }
    if (QMessageBox::question(this, "确认", "是否删除该医生？") != QMessageBox::Yes) return;

    QString docId = m_table->item(row, 0)->text();
    if (m_docModel->deleteDoctor(docId)) {
        QMessageBox::information(this, "成功", "医生删除完成");
        refreshTable(m_docModel->getAllDoctors());
    } else {
        QMessageBox::critical(this, "失败", "删除失败：" + m_docModel->lastError());
    }
}
