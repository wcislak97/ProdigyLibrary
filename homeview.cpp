#include "homeview.h"
#include "ui_homeview.h"
#include <QtDebug>

HomeView::HomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeView)
{
    ui->setupUi(this);
}

HomeView::~HomeView()
{
    delete ui;
}

void HomeView::on_pushButton_home_search_a_book_clicked()
{
    qDebug() << "Search book";

    QString title = ui->lineEdit_home_title->text();
    QString first_name = ui->lineEdit_home_first_name->text();
    QString last_name = ui->lineEdit_home_last_name->text();
}

void HomeView::on_pushButton_home_your_account_clicked()
{
    qDebug() << "Your Account";
}
