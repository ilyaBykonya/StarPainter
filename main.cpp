#include "StarPainterApplication/StarPainterApplication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StarPainterApplication appWindow;
    appWindow.show();
    return app.exec();
}
