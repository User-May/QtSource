#include "PatientController.h"

PatientController::PatientController(PatientWidget* view, PatientModel* model) : QObject(view) {
    m_view = view;
    m_model = model;

    // 初始化表格
    m_view->refreshPatientTable(m_model->getAllPatients());

    // 连接所有信号槽（重点补充修改/删除的连接）
    bool connSearch = connect(m_view, &PatientWidget::searchRequested, this, &PatientController::onSearchRequested);
    bool connAdd = connect(m_view, &PatientWidget::addPatientRequested, this, &PatientController::onAddPatientRequested);
    bool connUpdate = connect(m_view, &PatientWidget::updatePatientRequested, this, &PatientController::onUpdatePatientRequested);
    bool connDelete = connect(m_view, &PatientWidget::deletePatientRequested, this, &PatientController::onDeletePatientRequested);

    // 打印连接结果（必须全为true，否则连接失败）
    qDebug() << "信号槽连接结果：查询=" << connSearch << "添加=" << connAdd << "修改=" << connUpdate << "删除=" << connDelete;
    qDebug() << "修改信号地址：" << &PatientWidget::updatePatientRequested; // 验证信号存在
}

void PatientController::onSearchRequested(const QString& name) {
    // 新增：这行必须最先打印，确认槽函数是否触发
    qDebug() << "==========进入查询槽函数==========";
    qDebug() << "查询关键词：" << name;

    QList<Patient> patients;
    if (name.trimmed().isEmpty()) {
        qDebug() << "关键词为空，加载全量患者";
        patients = m_model->getAllPatients();
    } else {
        qDebug() << "关键词非空，执行模糊查询";
        patients = m_model->searchPatientByName(name);
    }
    qDebug() << "查询结果数量：" << patients.size();
    m_view->refreshPatientTable(patients);
}

void PatientController::onAddPatientRequested(const Patient& patient) {
    // 新增：打印接收到的患者信息
    qDebug() << "==========进入Controller添加逻辑==========";
    qDebug() << "Controller接收到添加请求：ID=" << patient.id << "姓名=" << patient.name;

    // 新增：检查必填字段是否为空（ID、姓名、身份证号是数据库非空字段）
    if (patient.id.isEmpty() || patient.name.isEmpty() || patient.idCard.isEmpty()) {
        QMessageBox::warning(m_view, "提示", "ID、姓名、身份证号不能为空！");
        return;
    }

    if (m_model->addPatient(patient)) {
        QMessageBox::information(m_view, "成功", "患者添加成功！");
        m_view->refreshPatientTable(m_model->getAllPatients());
    } else {
        // 新增：打印数据库插入失败的具体原因
        qDebug() << "患者添加失败：数据库执行错误";
        QMessageBox::critical(m_view, "失败", "患者添加失败！请检查输入或数据库连接");
    }
}

// 修改患者槽函数
void PatientController::onUpdatePatientRequested(const Patient& patient) {
    qDebug() << "==========进入修改槽函数==========";
    qDebug() << "待修改患者ID：" << patient.id << "，姓名：" << patient.name;

    if (m_model->updatePatient(patient)) {
        QMessageBox::information(m_view, "成功", "患者信息修改成功！");
        m_view->refreshPatientTable(m_model->getAllPatients()); // 刷新表格
    } else {
        QMessageBox::critical(m_view, "失败", "修改失败：" + m_model->lastError());
    }
}

// 删除患者槽函数
void PatientController::onDeletePatientRequested(const QString& patientId) {
    qDebug() << "==========进入删除槽函数==========";
    qDebug() << "待删除患者ID：" << patientId;

    if (m_model->deletePatient(patientId)) {
        QMessageBox::information(m_view, "成功", "患者删除成功！");
        m_view->refreshPatientTable(m_model->getAllPatients()); // 刷新表格
    } else {
        QMessageBox::critical(m_view, "失败", "删除失败：" + m_model->lastError());
    }
}
