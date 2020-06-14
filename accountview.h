#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H
#include "loginview.h"
#include <QWidget>

namespace Ui {
class accountview;
}

class accountview : public QWidget
{
    Q_OBJECT

public:
    explicit accountview(QWidget *parent = nullptr);
    ~accountview();

private slots:
    void on_pushButton_home_search_a_book_2_clicked();

    void on_pushButton_change_password_clicked();

    void on_pushButton_see_books_clicked();

private:
    Ui::accountview *ui;
};

#endif // ACCOUNTVIEW_H
