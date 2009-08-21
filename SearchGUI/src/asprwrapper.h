#ifndef ASPRWRAPPER_H
#define ASPRWRAPPER_H

#include <QString>

#ifdef WIN32
#include "windows.h"
#include "aspr_api.h"
#include "asprotect.h"
#endif


class CAsprWrapper
{
public:

    CAsprWrapper();

    bool IsModeActive( size_t stModeId );

    QString GetHwId();

    QString GetRegName();

    size_t GetDaysLeft();

    size_t GetExecLeft();

    void CheckEnvelope();

};

#endif // ASPRWRAPPER_H
