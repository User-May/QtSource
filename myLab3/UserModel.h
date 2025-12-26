#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QSqlDatabase>

class UserModel {
public:
    bool checkLogin(const QString& username, const QString& password);
    QString getUserIdByUsername(const QString& username);
};

#endif // USERMODEL_H
