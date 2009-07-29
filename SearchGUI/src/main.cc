#include <QApplication>
#include <log.h>
#include "qsearchwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSearchWindow window;
    window.show();
    
    return app.exec();
}
