#include "AddPatientDialog.h"
#include <QVBoxLayout>
#include <QLabel>

AddPatientDialog::AddPatientDialog(QWidget *parent, const Patient& patient) : QDialog(parent) {
    setWindowTitle(patient.id.isEmpty() ? "添加患者" : "修改患者");
    QVBoxLayout* layout = new QVBoxLayout(this);

    // 患者ID
    layout->addWidget(new QLabel("患者ID："));
    m_idEdit = new QLineEdit(patient.id);
    if (!patient.id.isEmpty()) m_idEdit->setEnabled(false); // 修改时ID不可改
    layout->addWidget(m_idEdit);

    // 身份证号
    layout->addWidget(new QLabel("身份证号："));
    m_idCardEdit = new QLineEdit(patient.idCard);
    layout->addWidget(m_idCardEdit);

    // 姓名
    layout->addWidget(new QLabel("姓名："));
    m_nameEdit = new QLineEdit(patient.name);
    layout->addWidget(m_nameEdit);

    // 性别
    layout->addWidget(new QLabel("性别："));
    m_sexCombo = new QComboBox();
    m_sexCombo->addItems({"女", "男"});
    m_sexCombo->setCurrentIndex(patient.sex);
    layout->addWidget(m_sexCombo);

    // 出生日期
    layout->addWidget(new QLabel("出生日期(yyyy-MM-dd)："));
    m_dobEdit = new QLineEdit(patient.dob);
    layout->addWidget(m_dobEdit);

    // 身高
    layout->addWidget(new QLabel("身高(m)："));
    m_heightEdit = new QLineEdit(QString::number(patient.height));
    layout->addWidget(m_heightEdit);

    // 体重
    layout->addWidget(new QLabel("体重(kg)："));
    m_weightEdit = new QLineEdit(QString::number(patient.weight));
    layout->addWidget(m_weightEdit);

    // 手机号
    layout->addWidget(new QLabel("手机号："));
    m_mobileEdit = new QLineEdit(patient.mobile);
    layout->addWidget(m_mobileEdit);

    // 年龄
    layout->addWidget(new QLabel("年龄："));
    m_ageEdit = new QLineEdit(QString::number(patient.age));
    layout->addWidget(m_ageEdit);

    // 按钮
    QPushButton* okBtn = new QPushButton("确定");
    QPushButton* cancelBtn = new QPushButton("取消");
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

Patient AddPatientDialog::getPatient() const {
    Patient p;
    p.id = m_idEdit->text().trimmed();
    p.idCard = m_idCardEdit->text().trimmed();
    p.name = m_nameEdit->text().trimmed();
    p.sex = m_sexCombo->currentIndex();
    p.dob = m_dobEdit->text().trimmed();
    p.height = m_heightEdit->text().toDouble();
    p.weight = m_weightEdit->text().toDouble();
    p.mobile = m_mobileEdit->text().trimmed();
    p.age = m_ageEdit->text().toInt();
    return p;
}
