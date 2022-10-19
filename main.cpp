#include <QApplication>
#include "foundation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Foundation w;
    w.resize(1080,720);
    w.setWindowTitle("Geometry Madness");
    w.setWindowIcon(QIcon(":/new/prefix1/icon/thumbnail.png"));
    w.show();
    return app.exec();
}
