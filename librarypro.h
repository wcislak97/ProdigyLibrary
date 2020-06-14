#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>
#include "registration.h"
#include "homeview.h"
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

    void showHomeView();

    QSqlDatabase getDB();

    ~LibraryPro();

private:
    Ui::LibraryPro *ui;

    RegisterView *registerView;
    LoginView *loginView;
    HomeView *homeView;

};

#endif // LIBRARYPRO_H


