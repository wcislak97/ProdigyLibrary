#ifndef MANAGEBOOKSVIEW_H
#define MANAGEBOOKSVIEW_H
#include "adminhomepage.h"
#include <QWidget>

namespace Ui {
class manageBooksView;
}

class manageBooksView : public QWidget
{
    Q_OBJECT

public:
    explicit manageBooksView(QWidget *parent = nullptr);
    ~manageBooksView();

private slots:
    void on_pushButton_return_book_clicked();

    void on_pushButton_your_account_clicked();

    void on_pushButton_home_page_clicked();

    void on_pushButton_remove_book_clicked();

    void on_pushButton_remove_book_2_clicked();

    void on_pushButton_add_book_clicked();

private:
    Ui::manageBooksView *ui;
};

#endif // MANAGEBOOKSVIEW_H
