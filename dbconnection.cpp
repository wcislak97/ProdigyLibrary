#include "dbconnection.h"
#include <QStandardPaths>
#include <QCoreApplication>



void DBConnection::connClose() {
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}
bool DBConnection::connOpen() {
    //QString path=QStandardPaths::findExecutable("LibraryPro.exe");
    QString path=QCoreApplication::applicationDirPath()+"/prodigy.db";
    qDebug()<<path;
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
