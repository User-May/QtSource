#include "PatientWidget.h"
#include "AddPatientDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

PatientWidget::PatientWidget(QWidget *parent) : QWidget(parent) {
    // 顶部搜索栏
    QHBoxLayout* topLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("请输入患者姓名查询");
    m_searchBtn = new QPushButton("查询");
    topLayout->addWidget(m_searchEdit);
    topLayout->addWidget(m_searchBtn);

    // 按钮栏
    QHBoxLayout* btnLayout = new QHBoxLayout();
    m_addBtn = new QPushButton("添加");
    m_updateBtn = new QPushButton("修改");
    m_deleteBtn = new QPushButton("删除");
    btnLayout->addWidget(m_addBtn);
    btnLayout->addWidget(m_updateBtn);
    btnLayout->addWidget(m_deleteBtn);

    // 患者表格
    m_patientTable = new QTableWidget();
    m_patientTable->setColumnCount(9);
    m_patientTable->setHorizontalHeaderLabels({"ID", "身份证号", "姓名", "性别", "出生日期", "身高(m)", "体重(kg)", "手机号", "年龄"});
    m_patientTable->setSelectionBehavior(QTableWidget::SelectRows);

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(m_patientTable);

    // 信号连接
    connect(m_searchBtn, &QPushButton::clicked, this, &PatientWidget::onSearchBtnClicked);
    connect(m_addBtn, &QPushButton::clicked, this, &PatientWidget::onAddBtnClicked);
    connect(m_updateBtn, &QPushButton::clicked, this, &PatientWidget::onUpdateBtnClicked);
    connect(m_deleteBtn, &QPushButton::clicked, this, &PatientWidget::onDeleteBtnClicked);
    // 注释原有信号emit逻辑，改为直接连接查询按钮到本地槽函数
    connect(m_searchBtn, &QPushButton::clicked, this, &PatientWidget::onSearchDirect);
    // 保留原有信号连接（用于后续验证）
    connect(m_searchBtn, &QPushButton::clicked, this, &PatientWidget::onSearchBtnClicked);
}

void PatientWidget::refreshPatientTable(const QList<Patient>& patients) {
    m_patientTable->setRowCount(0);
    for (int i = 0; i < patients.size(); ++i) {
        const Patient& p = patients[i];
        m_patientTable->insertRow(i);
        m_patientTable->setItem(i, 0, new QTableWidgetItem(p.id));
        m_patientTable->setItem(i, 1, new QTableWidgetItem(p.idCard));
        m_patientTable->setItem(i, 2, new QTableWidgetItem(p.name));
        m_patientTable->setItem(i, 3, new QTableWidgetItem(p.sex == 0 ? "女" : "男"));
        m_patientTable->setItem(i, 4, new QTableWidgetItem(p.dob));
        m_patientTable->setItem(i, 5, new QTableWidgetItem(QString::number(p.height)));
        m_patientTable->setItem(i, 6, new QTableWidgetItem(QString::number(p.weight)));
        m_patientTable->setItem(i, 7, new QTableWidgetItem(p.mobile));
        m_patientTable->setItem(i, 8, new QTableWidgetItem(QString::number(p.age)));
    }
}

void PatientWidget::onSearchBtnClicked() {
    // 修正：trimmed()去除首尾空格，避免输入空格导致查询失败
    QString searchName = m_searchEdit->text().trimmed();
    qDebug() << "点击查询，关键词：" << searchName;
    emit searchRequested(searchName);
}

void PatientWidget::onAddBtnClicked() {
    AddPatientDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Patient p = dialog.getPatient();
        qDebug() << "准备添加患者：ID=" << p.id << "姓名=" << p.name;

        // 直接调用Model添加
        PatientModel model;
        if (model.addPatient(p)) {
            QMessageBox::information(this, "成功", "患者添加成功！");
            refreshPatientTable(model.getAllPatients()); // 刷新表格
        } else {
            QMessageBox::critical(this, "失败", "患者添加失败！");
        }
    }
}

void PatientWidget::onUpdateBtnClicked() {
    int row = m_patientTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要修改的患者");
        return;
    }

    // 提取原始数据（和你原有代码一致）
    QString patientId = m_patientTable->item(row, 0)->text();
    Patient p;
    p.id = patientId;
    p.idCard = m_patientTable->item(row, 1)->text();
    p.name = m_patientTable->item(row, 2)->text();
    p.sex = m_patientTable->item(row, 3)->text() == "女" ? 0 : 1;
    p.dob = m_patientTable->item(row, 4)->text();
    p.height = m_patientTable->item(row, 5)->text().toDouble();
    p.weight = m_patientTable->item(row, 6)->text().toDouble();
    p.mobile = m_patientTable->item(row, 7)->text();
    p.age = m_patientTable->item(row, 8)->text().toInt();

    // 打开修改对话框
    AddPatientDialog dialog(this, p);
    if (dialog.exec() == QDialog::Accepted) {
        Patient updatedPatient = dialog.getPatient();

        // ===== 核心：直接调用Model =====
        PatientModel model;
        bool result = model.updatePatient(updatedPatient);
        if (result) {
            QMessageBox::information(this, "成功", "患者信息修改成功！");
            // 刷新表格
            QList<Patient> patients = model.getAllPatients();
            refreshPatientTable(patients); // 你的表格刷新函数
        } else {
            QMessageBox::critical(this, "失败", model.lastError());
        }
    }
}

void PatientWidget::onDeleteBtnClicked() {
    int row = m_patientTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "提示", "请选择要删除的患者！");
        return;
    }

    QString patientId = m_patientTable->item(row, 0)->text();
    qDebug() << "【删除按钮】选中行号：" << row;
    qDebug() << "【删除按钮】选中患者ID：" << patientId;

    if (QMessageBox::question(this, "确认删除", "是否确定删除ID为" + patientId + "的患者？",
        QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }
    qDebug() << "【删除按钮】确认删除，ID：" << patientId;

    // ===== 新增调试：确认执行到Model调用 =====
    qDebug() << "【删除按钮】开始调用Model的deletePatient函数";
    PatientModel model;
    if (model.deletePatient(patientId)) {
        QMessageBox::information(this, "成功", "患者删除成功！");
        refreshPatientTable(model.getAllPatients());
    } else {
        QMessageBox::critical(this, "失败", "删除失败：" + model.lastError());
    }
    qDebug() << "【删除按钮】Model调用完成";
}

// 本地查询函数（绕开Controller，直接调用Model）
void PatientWidget::onSearchDirect() {
    // 1. 获取搜索框输入（去空格）
    QString rawName = m_searchEdit->text();
    QString searchName = rawName.trimmed();
    qDebug() << "【本地查询】原始输入：" << rawName << " | 处理后：" << searchName;

    // 2. 调用Model查询
    PatientModel model;
    QList<Patient> patients;
    if (searchName.isEmpty()) {
        // 空关键词 → 加载所有患者
        patients = model.getAllPatients();
        qDebug() << "【本地查询】加载全量患者，数量：" << patients.size();
    } else {
        // 非空 → 模糊查询
        patients = model.searchPatientByName(searchName);
        qDebug() << "【本地查询】模糊查询结果数量：" << patients.size();
    }

    // 3. 刷新表格 + 弹窗提示
    refreshPatientTable(patients);
    if (patients.isEmpty()) {
        QMessageBox::information(this, "提示", "未找到匹配的患者！");
    } else {
        QMessageBox::information(this, "提示", QString("共找到 %1 位患者").arg(patients.size()));
    }
}


