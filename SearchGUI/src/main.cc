#include <QtPlugin>
#include <QApplication>
#include <log.hpp>
#include "qsearchwindow.h"

Q_IMPORT_PLUGIN(qgif)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CUserLog() << "FileOrganizer started" << std::endl;
    QSearchWindow window;
    window.show();
    
    return app.exec();
}
