#ifndef PATIENTCONTROLLER_H
#define PATIENTCONTROLLER_H

#include <QObject>
#include "PatientWidget.h"
#include "PatientModel.h"
#include <QMessageBox>

class PatientController : public QObject {
    Q_OBJECT
public:
    explicit PatientController(PatientWidget* view, PatientModel* model);
private slots:
    void onSearchRequested(const QString& name);
    void onAddPatientRequested(const Patient& patient);
    void onUpdatePatientRequested(const Patient& patient);
    void onDeletePatientRequested(const QString& patientId);
private:
    PatientWidget* m_view;
    PatientModel* m_model;
};

#endif // PATIENTCONTROLLER_H
