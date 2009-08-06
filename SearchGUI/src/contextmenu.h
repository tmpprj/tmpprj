#ifndef CCONTEXTMENU_H
#define CCONTEXTMENU_H

#include <QString>
#include <QPoint>
#include <QWidget>
#include <comwrapper.hpp>
#ifdef WIN32
#include <windows.h>
#include <shlobj.h>
#endif

class CContextMenu
{
public:

    CContextMenu( WId WinId );
    ~CContextMenu();

    void Show( QPoint ptWhere, QString strFileName );
    void InvokeDefault( QString strFileName );

private:

    std::pair<QString, QString> ParsePath( QString strPath );

#ifdef WIN32
    bool GetUIObjectOfFile( const QString& strFileName, CComWrapper<IContextMenu>& CM );
    static LRESULT CALLBACK HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    CComWrapper<IShellFolder> m_DesktopFolder;
    CComWrapper<IMalloc> m_Malloc;
#endif
    WId m_WinId;

};




#endif // CCONTEXTMENU_H
