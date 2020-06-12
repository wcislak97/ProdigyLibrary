#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class RegisterView;
}

class RegisterView : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterView(QWidget *parent = nullptr);
    ~RegisterView();

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_register_clicked();

private:
    Ui::RegisterView *ui;
};

#endif // REGISTER_H
