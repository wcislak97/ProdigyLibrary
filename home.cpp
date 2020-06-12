#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_pushButton_search_a_book_clicked()
{
    QString title = ui->lineEdit_title->text();
    QString first_name = ui->lineEdit_first_name->text();
    QString last_name = ui->lineEdit_last_name->text();
}
