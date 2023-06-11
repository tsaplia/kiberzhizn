#include "CyberLife.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CyberLife w;
    w.show();
    return a.exec();
}
