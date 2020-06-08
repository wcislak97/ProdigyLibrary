#ifndef LIBRARYPRO_H
#define LIBRARYPRO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LibraryPro; }
QT_END_NAMESPACE

class LibraryPro : public QMainWindow
{
    Q_OBJECT

public:
    LibraryPro(QWidget *parent = nullptr);
    ~LibraryPro();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LibraryPro *ui;
};
#endif // LIBRARYPRO_H
