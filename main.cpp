#include "librarypro.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibraryPro w;
    w.show();
    return a.exec();
}
