#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_homeTemp_clicked();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
