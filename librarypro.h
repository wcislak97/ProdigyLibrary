#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>
#include "registration.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class LibraryPro; }
QT_END_NAMESPACE

class LibraryPro : public QMainWindow
{
    Q_OBJECT

public:
    LibraryPro(QWidget *parent = nullptr);
    ~LibraryPro();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

private:
    Ui::LibraryPro *ui;
    Registration *registration;
};

#endif // LIBRARYPRO_H


class DBConnection{
public:
    QSqlDatabase mydb;


    void connClose(){
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);

    }


    bool connOpen()
    {
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
};
