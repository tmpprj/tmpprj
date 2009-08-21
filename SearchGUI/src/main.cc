#include <QApplication>
#include <QMessageBox>
#include <log.h>
#include "qsearchwindow.h"

#include "qregisterdialog.h"
#include "asprwrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSearchWindow window;

    CAsprWrapper aspr;
    aspr.CheckEnvelope();
    if( !aspr.IsModeActive(1) )
    {
        if( aspr.GetDaysLeft() < 1 || aspr.GetExecLeft() < 1 )
        {
            QMessageBox::warning( &window, "Warning", "Your trial period is expired. Please register at www.atalantasoft.com" );
            QRegisterDialog RegisterDlg( &window );
            if( QDialog::Accepted != RegisterDlg.exec() )
                return 1;
        }
        else if( 0 == aspr.GetExecLeft()%5 )
            QMessageBox::information( &window, "Information", "You are using unregistered version. Please register at www.atalantasoft.com" );
    }

    window.show();
    
    return app.exec();
}
