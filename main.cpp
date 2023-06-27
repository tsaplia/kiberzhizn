#include "cyber_life.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    srand(time(NULL));
    CyberLife w;
    w.resize(900, 500);
    w.show();
    return a.exec();
}
