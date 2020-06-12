#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>

namespace Ui {
class HomeView;
}

class HomeView : public QWidget
{
    Q_OBJECT

public:
    explicit HomeView(QWidget *parent = nullptr);
    ~HomeView();

private slots:
    void on_pushButton_home_search_a_book_clicked();
    void on_pushButton_home_your_account_clicked();

private:
    Ui::HomeView *ui;
};

#endif // HOMEVIEW_H
