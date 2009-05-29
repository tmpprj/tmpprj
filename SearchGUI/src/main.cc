#include <QApplication>
#include <log.hpp>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSearchWindow window;

    window.show();
    return app.exec();
}
