#ifndef ADMINACCOUNTVIEW_H
#define ADMINACCOUNTVIEW_H

#include <QWidget>

namespace Ui {
class adminaccountview;
}

class adminaccountview : public QWidget
{
    Q_OBJECT

public:
    explicit adminaccountview(QWidget *parent = nullptr);
    ~adminaccountview();

private slots:
    void on_pushButton_see_books_clicked();

    void on_pushButton_home_search_a_book_2_clicked();

    void on_pushButton_manage_books_clicked();

    void on_pushButton_change_password_clicked();

private:
    Ui::adminaccountview *ui;
};

#endif // ADMINACCOUNTVIEW_H
