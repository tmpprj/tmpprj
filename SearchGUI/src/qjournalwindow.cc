#include <QtGui>
#include "qjournalwindow.h"
#include "log.hpp"

QJournalWindow::QJournalWindow( QWidget *parent )
    : QDialog( parent )
{
    setupUi( this );

    journalEdit->setText( CUserLog().GetLogData().c_str() );
}

