#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>
#include "registration.h"
#include "home.h"
#include "registerview.h"
#include "loginview.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
    class LibraryPro;
}
QT_END_NAMESPACE

class LibraryPro : public QMainWindow
{
    Q_OBJECT

public:
    LibraryPro(QWidget *parent = nullptr);

    void showLoginView();

    void showRegisterView();

    QSqlDatabase getDB();

    ~LibraryPro();

private:
    Ui::LibraryPro *ui;
    Home *home;
    RegisterView *registerWidget;
    LoginView *loginView;
    QSqlDatabase mydb;
};

#endif // LIBRARYPRO_H


