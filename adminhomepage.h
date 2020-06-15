#ifndef ADMINHOMEPAGE_H
#define ADMINHOMEPAGE_H
#include "loginview.h"
#include <QWidget>


namespace Ui {
class adminHomePage;
}

class adminHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit adminHomePage(QWidget *parent = nullptr);
    ~adminHomePage();

private slots:
    void on_pushButton_home_search_a_book_3_clicked();

    void on_pushButton_your_account_clicked();

    void on_pushButton_manage_books_clicked();

    void on_bookIt_button_3_clicked();

    void on_actual_search_button_clicked();

private:
    Ui::adminHomePage *ui;
};

#endif // ADMINHOMEPAGE_H
