#include "MainWindow.h"
#include <QApplication>
#include <boost/shared_ptr.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();    
    return a.exec();
}
