#include <QtGui/QApplication>
#include "controller.h"

#include "customer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c;

    return a.exec();
}
