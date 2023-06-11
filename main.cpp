#include "cyber_life.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CyberLife w;
    w.resize(300, 300);
    w.show();
    return a.exec();
}
