#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>
#include "registration.h"
#include "home.h"
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
<<<<<<< HEAD
    Home *home;
    QSqlDatabase mydb;
=======
>>>>>>> 8c8f32a6f1c348c91bc7e8f6a6d008568d7db3d4
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
