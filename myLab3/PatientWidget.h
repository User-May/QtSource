#ifndef PATIENTWIDGET_H
#define PATIENTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "PatientModel.h"

class PatientWidget : public QWidget {
    Q_OBJECT
public:
    explicit PatientWidget(QWidget *parent = nullptr);
    void refreshPatientTable(const QList<Patient>& patients);
signals:
    void searchRequested(const QString& name);
    void addPatientRequested(const Patient& patient);
    void updatePatientRequested(const Patient& patient);
    void deletePatientRequested(const QString& patientId);
private slots:
    void onSearchBtnClicked();
    void onAddBtnClicked();
    void onUpdateBtnClicked();
    void onDeleteBtnClicked();
    void onSearchDirect();
private:
    QLineEdit* m_searchEdit;
    QPushButton* m_searchBtn;
    QPushButton* m_addBtn;
    QPushButton* m_updateBtn;
    QPushButton* m_deleteBtn;
    QTableWidget* m_patientTable;
};

#endif // PATIENTWIDGET_H
