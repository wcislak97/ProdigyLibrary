#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>
#include "homeview.h"
#include "registerview.h"
#include "loginview.h"
#include "accountview.h"
#include "adminhomepage.h"
#include "managebooksview.h"
#include "adminaccountview.h"
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

    void showAccountView();

    void showAdminHomePage();

    void showManageBooks();

    void showAdminAccountView();

    QSqlDatabase getDB();

    ~LibraryPro();

private:
    Ui::LibraryPro *ui;

    adminHomePage *adminhomepage;
    RegisterView *registerView;
    LoginView *loginView;
    HomeView *homeView;
    accountview *accountView;
    manageBooksView *managebooksview;
    adminaccountview *adminAccountView;

};

#endif // LIBRARYPRO_H


