#include "asprwrapper.h"

#ifdef WIN31
#include "aspr.h"
#endif

CAsprWrapper::CAsprWrapper()
{
}

bool CAsprWrapper::IsModeActive( size_t stModeId )
{
#ifdef WIN32
    MODE_STATUS ModeStatus;
    char* ModeName;

    GetModeInformation( stModeId, &ModeName, &ModeStatus );

    return ModeStatus.IsModeActivated;
#else
    return true;
#endif
}

QString CAsprWrapper::GetHwId()
{
#ifdef WIN32
    return QString( GetHardwareID() );
#else
    return "";
#endif
}

QString CAsprWrapper::GetRegName()
{
#ifdef WIN32
    char *Key = "", *Name = "";
    GetRegistrationInformation( 0, &Key, &Name );
    return QString( Name );
#else
    return "";
#endif
}

size_t CAsprWrapper::GetDaysLeft()
{
#ifdef WIN32
    DWORD DaysTotal, DaysLeft;
    GetTrialDays( 0, &DaysTotal, &DaysLeft );
    return DaysLeft;
#else
    return 0;
#endif
}

size_t CAsprWrapper::GetExecLeft()
{
#ifdef WIN32
    DWORD ExTotal, ExLeft;
    GetTrialExecs( 0, &ExTotal, &ExLeft );
    return ExLeft;
#else
    return 0;
#endif
}

#ifdef WIN32
BOOL EnvelopeCheck()
{
USER_POLYBUFFER
#include "CppEnvelopeCheckFunc.inc"
}
#endif

void CAsprWrapper::CheckEnvelope()
{
#ifdef WIN32
USER_POLYBUFFER
        //TODO: doesn`t work
   EnvelopeCheck();
#endif
}

bool CAsprWrapper::TryRegiter( const QString& strName, const QString& strKey )
{
#ifdef WIN32
    return CheckKeyAndDecrypt( strKey.toLatin1().data(), strName.toLatin1().data(), TRUE );
#else
    return true;
#endif
}
