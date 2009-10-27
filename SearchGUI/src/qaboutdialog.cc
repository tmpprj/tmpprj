#include "qaboutdialog.h"
#include <QMessageBox>

QAboutDialog::QAboutDialog( QWidget *parent )
: QDialog( parent, Qt::WindowContextHelpButtonHint | Qt::Dialog  )
{
    setupUi( this );
    RefreshData();
}

void QAboutDialog::RefreshData()
{
    versionLabel->setText( REVISION );
    if( m_Aspr.IsModeActive(1) )
        SetupRegisteredControls();
    else
        SetupTrialControls();
}

QAboutDialog::~QAboutDialog(void)
{
}

void QAboutDialog::SetupRegisteredControls()
{
    hwidEdit->setText( m_Aspr.GetHwId() );
    regnameLabel->setText( m_Aspr.GetRegName() );
    daysleftLabel->setText( "Unlimited" );
    exleftLabel->setText( "Unlimited" );
    registerButton->hide();
}

void QAboutDialog::SetupTrialControls()
{
    hwidEdit->setText( m_Aspr.GetHwId() );
    regnameLabel->setText( "Trial version" );
    daysleftLabel->setText( QString::number( m_Aspr.GetDaysLeft() ) );
    exleftLabel->setText( QString::number( m_Aspr.GetExecLeft() ) );
    registerButton->show();
    connect( registerButton, SIGNAL( clicked() ), this, SLOT( Register() ) );
}

void QAboutDialog::Register()
{
    QRegisterDialog RegisterDlg( this );
    if( QDialog::Accepted == RegisterDlg.exec() )
        close();
}

