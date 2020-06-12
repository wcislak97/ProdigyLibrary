#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_pushButton_search_a_book_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
