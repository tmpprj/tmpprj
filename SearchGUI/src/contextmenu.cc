#include <contextmenu.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <boost/concept_check.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <log.hpp>
#include <menuwrapper.hpp>

#define SCRATCH_QCM_FIRST 1
#define SCRATCH_QCM_LAST  0x7FFF

#ifdef WIN32
CComWrapper<IContextMenu2> g_Pcm2;
CComWrapper<IContextMenu3> g_Pcm3;
boost::mutex g_mtx;
#endif

CContextMenu::CContextMenu( WId WinId ):m_WinId( WinId )
{
#ifdef WIN32
    // Get an IShellFolder for the desktop.
    SHGetDesktopFolder( m_DesktopFolder.Set() );
    SHGetMalloc( (IMalloc**)m_Malloc.Set() );
#endif
}

CContextMenu::~CContextMenu()
{
#ifdef WIN32
#endif
}

void CContextMenu::Show( QPoint ptWhere, QString strFileName )
{
#ifdef WIN32
    // Get the IContextMenu for the file.
    CComWrapper<IContextMenu> CM;
    GetUIObjectOfFile( strFileName, CM );

    CMenuWrapper Menu( CreatePopupMenu() );
    DWORD Flags = CMF_EXPLORE; //CMF_NORMAL?
    CM.Get()->QueryContextMenu( Menu.Get(), 0, SCRATCH_QCM_FIRST, SCRATCH_QCM_LAST, Flags );

    CM.Get()->QueryInterface( IID_IContextMenu2, (void**)g_Pcm2.Set() );
    CM.Get()->QueryInterface( IID_IContextMenu3, (void**)g_Pcm3.Set() );

    // subclass window to handle menurelated messages in CShellContextMenu
    WNDPROC OldWndProc;
    if( NULL != g_Pcm2.Get() || NULL != g_Pcm3.Get() )
        OldWndProc = (WNDPROC)SetWindowLong( m_WinId, GWL_WNDPROC, (DWORD)HookWndProc );
    else
        OldWndProc = NULL;

    int Cmd = TrackPopupMenuEx( Menu.Get(), TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, ptWhere.x(), ptWhere.y(), m_WinId, 0 );
    if(OldWndProc) // unsubclass
        SetWindowLong( m_WinId, GWL_WNDPROC, (DWORD) OldWndProc );

    if (Cmd < 100 && Cmd != 0)
    {
        CMINVOKECOMMANDINFO info = { 0 };
        info.cbSize = sizeof(info);
        info.hwnd = m_WinId;
        info.lpVerb  = MAKEINTRESOURCEA(Cmd - SCRATCH_QCM_FIRST);
        info.nShow = SW_SHOWNORMAL;
        CM.Get()->InvokeCommand(&info);
    }

    g_Pcm2.Clear();
    g_Pcm3.Clear();
#else
    boost::ignore_unused_variable_warning( strFileName );
    boost::ignore_unused_variable_warning( ptWhere );
#endif
}

#ifdef WIN32

bool CContextMenu::GetUIObjectOfFile( const QString& strFileName, CComWrapper<IContextMenu>& CM )
{
    if( NULL == m_DesktopFolder.Get() || NULL == m_Malloc.Get() )
    {
        CLog( debug ) << "CContextMenu::GetUIObjectOfFile: not initialized";
        return false;
    }

    wchar_t Path[MAX_PATH], FileName[MAX_PATH];
    ::memset( Path, 0, sizeof(Path) );
    ::memset( FileName, 0, sizeof(FileName) );
    QFileInfo pathInfo( strFileName );
    QDir::toNativeSeparators( pathInfo.fileName() ).toWCharArray( FileName );
    QDir::toNativeSeparators( pathInfo.absolutePath() ).toWCharArray( Path );

    // Get a pidl for the folder the file
    // is located in.
    LPITEMIDLIST ParentPidl;
    DWORD Eaten;
    DWORD Result = m_DesktopFolder.Get()->ParseDisplayName( m_WinId, 0, Path, &Eaten, &ParentPidl, 0);
    if( Result != NOERROR )
    {
        CLog( debug ) << "CContextMenu::GetUIObjectOfFile: Invalid file name: " << strFileName << " error = " << Result;
        return false;
    }

    // Get an IShellFolder for the folder
    // the file is located in.
    CComWrapper<IShellFolder> ParentFolder;
    Result = m_DesktopFolder.Get()->BindToObject( ParentPidl, 0, IID_IShellFolder, (void**)ParentFolder.Set() );
    m_Malloc.Get()->Free( ParentPidl );
    if( NULL == ParentFolder.Get() )
    {
        CLog( debug ) << "CContextMenu::GetUIObjectOfFile: Invalid file name: " << strFileName;
        return false;
    }

    // Get a pidl for the file itself.
    LPITEMIDLIST Pidl;
    ParentFolder.Get()->ParseDisplayName( m_WinId, 0, FileName, &Eaten, &Pidl, 0 );

    // Get the IContextMenu for the file.

    ParentFolder.Get()->GetUIObjectOf( m_WinId, 1, (LPCITEMIDLIST*)&Pidl, IID_IContextMenu, 0, (void**)CM.Set() );
    m_Malloc.Get()->Free( Pidl );
    if( !CM.Get() )
    {
        CLog( debug ) << "CContextMenu::GetUIObjectOfFile: Unable to get context menu interface";
        return false;
    }
    return true;
}
#endif

void CContextMenu::InvokeDefault( QString strFileName )
{
#ifdef WIN32
    CComWrapper<IContextMenu> Pcm;
    wchar_t Path[MAX_PATH];
    ::memset( Path, 0, sizeof(Path) );
    strFileName.toWCharArray(Path);
    if( SUCCEEDED( GetUIObjectOfFile( strFileName, Pcm ) ) )
    {
        CMenuWrapper Menu( CreatePopupMenu() );
        if( Menu.Get() )
        {
            if( SUCCEEDED( Pcm.Get()->QueryContextMenu( Menu.Get(), 0,
                                                SCRATCH_QCM_FIRST, SCRATCH_QCM_LAST,
                                                CMF_DEFAULTONLY ) ) )
            {
                UINT id = GetMenuDefaultItem( Menu.Get(), FALSE, 0 );
                if( id != (UINT)-1 )
                {
                    CMINVOKECOMMANDINFO info = { 0 };
                    info.cbSize = sizeof(info);
                    info.hwnd = m_WinId;
                    info.lpVerb = MAKEINTRESOURCEA(id - SCRATCH_QCM_FIRST);
                    info.nShow = SW_SHOWNORMAL;
                    Pcm.Get()->InvokeCommand(&info);
                }
            }
        }
    }
#else
    boost::ignore_unused_variable_warning( strFileName );
#endif
}

#ifdef WIN32

LRESULT CALLBACK CContextMenu::HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    boost::unique_lock<boost::mutex> lock( g_mtx );
    if( g_Pcm3.Get() )
    {
        LRESULT lres;
        if( SUCCEEDED( g_Pcm3.Get()->HandleMenuMsg2( message, wParam, lParam, &lres ) ) )
            return lres;
    }
    else if( g_Pcm2.Get() )
        if( SUCCEEDED( g_Pcm2.Get()->HandleMenuMsg( message, wParam, lParam ) ) )
            return 0;
    return ::CallWindowProc((WNDPROC)GetProp( hWnd, TEXT ("OldWndProc")), hWnd, message, wParam, lParam );
}
#endif


