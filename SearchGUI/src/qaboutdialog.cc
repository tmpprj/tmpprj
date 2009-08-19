#include "qaboutdialog.h"
#ifdef WIN32
#include "windows.h"
#include "aspr_api.h"
#include "asprotect.h"
#endif

QAboutDialog::QAboutDialog( QWidget *parent )
        : QDialog( parent )
{
    setupUi( this );
#ifdef WIN32
    m_strHardwareId = GetHardwareID();
#endif
    hwidEdit->setText( m_strHardwareId );
}

QAboutDialog::~QAboutDialog(void)
{
}
