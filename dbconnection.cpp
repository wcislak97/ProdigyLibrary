#include "dbconnection.h"


void DBConnection::connClose() {
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool DBConnection::connOpen() {
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./prodigy.db");

    if (!mydb.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}
