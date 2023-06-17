#include "cyber_life.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    CyberLife w;
    w.resize(600, 400);
    w.show();
    return a.exec();
}
