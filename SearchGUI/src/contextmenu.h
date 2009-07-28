#ifndef CCONTEXTMENU_H
#define CCONTEXTMENU_H

#include <QString>
#include <QPoint>
#include <QWidget>
#ifdef WIN32
#include <windows.h>
#include <shlobj.h>
#endif

class CContextMenu
{
public:

    CContextMenu( WId WinId );

    void Show( QPoint ptWhere, QString strFileName );
    void InvokeDefault( QString strFileName );

private:

#ifdef WIN32
    static LRESULT CALLBACK HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LPSHELLFOLDER m_DesktopFolder;
#endif
    WId m_WinId;

};

#endif // CCONTEXTMENU_H
