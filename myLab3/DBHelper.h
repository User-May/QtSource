#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QString>

class DBHelper {
public:
    static DBHelper* getInstance();
    QSqlDatabase getDB();

private:
    DBHelper();
    ~DBHelper();
    DBHelper(const DBHelper&) = delete;
    DBHelper& operator=(const DBHelper&) = delete;

    static DBHelper* m_instance;
    QSqlDatabase m_db;
};

#endif // DBHELPER_H
