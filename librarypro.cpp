#include "librarypro.h"
#include "ui_librarypro.h"
#include "loginview.h"
#include "registerview.h"
#include <fstream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

LibraryPro::LibraryPro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryPro)
{
    ui->setupUi(this);

    showLoginView();

}


LibraryPro::~LibraryPro()
{
    delete ui;
}

QSqlDatabase LibraryPro::getDB() {
    return mydb;
}

void LibraryPro::showLoginView()
{
    loginView = new LoginView();
    this->setCentralWidget(loginView);
}

void LibraryPro::showRegisterView()
{
    registerView = new RegisterView();
    this->setCentralWidget(registerView);
}

void LibraryPro::showHomeView()
{
    homeView = new HomeView();
    this->setCentralWidget(homeView);
}



