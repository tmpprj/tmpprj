#include "qaboutdialog.h"
#ifdef WIN32
#include "windows.h"
#include "aspr_api.h"
#include "asprotect.h"
#endif

QAboutDialog::QAboutDialog( QWidget *parent )
        : QDialog( parent )
        ,m_bRegistered(false)
        ,m_stDaysTotal(0)
        ,m_stDaysLeft(0)
        ,m_stExTotal(0)
        ,m_stExLeft(0)
{
    setupUi( this );
    LoadData();

    versionLabel->setText( REVISION );
    if( m_bRegistered )
        SetupRegisteredControls();
    else
        SetupTrialControls();

}

void QAboutDialog::SetupRegisteredControls()
{
    hwidEdit->hide();
    hwidLabel->hide();

    regnameLabel->setText( m_strRegName );

    daysleftLabel->hide();
    daysleftCaptionLabel->hide();
    exleftLabel->hide();
    exleftCaptionLabel->hide();
}

void QAboutDialog::SetupTrialControls()
{
    hwidEdit->show();
    hwidLabel->show();
    hwidEdit->setText( m_strHardwareId );

    regnameLabel->setText( "Trial version" );

    daysleftLabel->show();
    daysleftLabel->setText( QString::number( m_stDaysLeft ) );

    exleftLabel->show();
    exleftLabel->setText( QString::number( m_stExLeft ) );
}

void QAboutDialog::LoadData()
{
#ifdef WIN32
    MODE_STATUS ModeStatus;
    char* ModeName;
    GetModeInformation( 1, &ModeName, &ModeStatus );
    m_bRegistered = ModeStatus.IsModeActivated;

    m_strHardwareId = GetHardwareID();

    char* Key = "";
    char* Name = "";
    GetRegistrationInformation( 0, &Key, &Name );
    m_strRegName = Name;

    DWORD DaysTotal, DaysLeft;
    GetTrialDays( 0, &DaysTotal, &DaysLeft );
    m_stDaysTotal = DaysTotal;
    m_stDaysLeft = DaysLeft;

    DWORD ExTotal, ExLeft;
    GetTrialExecs( 0, &ExTotal, &ExLeft );
    m_stExTotal = ExTotal;
    m_stExLeft = ExLeft;
#endif
}

QAboutDialog::~QAboutDialog(void)
{
}
