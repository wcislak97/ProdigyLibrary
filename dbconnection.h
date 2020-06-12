#include <QtSql>
#ifndef DBCONNECTION_H
#define DBCONNECTION_H


class DBConnection{
public:
    QSqlDatabase mydb;

    void connClose();

    bool connOpen();
};


#endif // DBCONNECTION_H
