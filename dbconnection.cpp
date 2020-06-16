#include "dbconnection.h"
#include <QStandardPaths>
#include <QCoreApplication>



//method to close connection with the database
void DBConnection::connClose() {
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

//method to open connection with the database
bool DBConnection::connOpen() {

    //setting root of the DB to path that contains executable file
    QString path=QCoreApplication::applicationDirPath()+"/prodigy.db";

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(path);

    if (!mydb.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}
