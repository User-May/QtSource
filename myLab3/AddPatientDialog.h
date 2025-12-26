#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "PatientModel.h"

class AddPatientDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddPatientDialog(QWidget *parent = nullptr, const Patient& patient = Patient());
    Patient getPatient() const;
private:
    QLineEdit* m_idEdit;
    QLineEdit* m_idCardEdit;
    QLineEdit* m_nameEdit;
    QComboBox* m_sexCombo;
    QLineEdit* m_dobEdit;
    QLineEdit* m_heightEdit;
    QLineEdit* m_weightEdit;
    QLineEdit* m_mobileEdit;
    QLineEdit* m_ageEdit;
};

#endif // ADDPATIENTDIALOG_H
