#include <contextmenu.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <boost/concept_check.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <log.h>
#include <menuwrapper.hpp>

#define SCRATCH_QCM_FIRST 1
#define SCRATCH_QCM_LAST  0x7FFF

#ifdef WIN32
CComWrapper<IContextMenu2> g_Pcm2;
CComWrapper<IContextMenu3> g_Pcm3;
WNDPROC g_OldWndProc;
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

std::pair<QString, QString> CContextMenu::ParsePath( QString strPath )
{
    std::pair<QString, QString> pairRes;
    int iEndPos = strPath.endsWith( QDir::separator() )? strPath.size()-2 : strPath.size()-1;
    int iPos = strPath.lastIndexOf( QDir::separator(), iEndPos );
    pairRes.first = strPath.mid( iPos+1, iEndPos-iPos );
    pairRes.second = strPath.left( iPos+1 );
    return pairRes;
}

void CContextMenu::Show( QPoint ptWhere, QString strFileName )
{
#ifdef WIN32
    // Get the IContextMenu for the file.
    CComWrapper<IContextMenu> CM;
    if( !GetUIObjectOfFile( strFileName, CM ) )
        return;

    CMenuWrapper Menu( CreatePopupMenu() );
    DWORD Flags = CMF_EXPLORE; //CMF_NORMAL?
    CM.Get()->QueryContextMenu( Menu.Get(), 0, SCRATCH_QCM_FIRST, SCRATCH_QCM_LAST, Flags );

    CM.Get()->QueryInterface( IID_IContextMenu2, (void**)g_Pcm2.Set() );
    CM.Get()->QueryInterface( IID_IContextMenu3, (void**)g_Pcm3.Set() );

    // subclass window to handle menurelated messages in CShellContextMenu

    if( NULL != g_Pcm2.Get() || NULL != g_Pcm3.Get() )
        g_OldWndProc = (WNDPROC)::SetWindowLongPtr( m_WinId, GWLP_WNDPROC, (LONG_PTR)HookWndProc );
    else
        g_OldWndProc = NULL;

    int Cmd = TrackPopupMenuEx( Menu.Get(), TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, ptWhere.x(), ptWhere.y(), m_WinId, 0 );
    if( g_OldWndProc ) // unsubclass
        ::SetWindowLongPtr( m_WinId, GWLP_WNDPROC, (LONG_PTR) g_OldWndProc );

    if( Cmd != -1 )
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
        CLog( Debug ) << "CContextMenu::GetUIObjectOfFile: not initialized";
        return false;
    }
    boost::unique_lock<boost::mutex> lock( g_mtx );

    wchar_t Path[MAX_PATH], FileName[MAX_PATH];
    ::memset( Path, 0, sizeof(Path) );
    ::memset( FileName, 0, sizeof(FileName) );
    std::pair< QString, QString > pairPath = ParsePath( QDir::toNativeSeparators( strFileName ) );
    pairPath.first.toWCharArray( FileName );
    pairPath.second.toWCharArray( Path );

    // Get a pidl for the folder the file
    // is located in.
    LPITEMIDLIST ParentPidl;
    DWORD Eaten;
    DWORD Result = m_DesktopFolder.Get()->ParseDisplayName( m_WinId, 0, Path, &Eaten, &ParentPidl, 0);
    if( Result != NOERROR )
    {
        CLog( Debug ) << "CContextMenu::GetUIObjectOfFile: Invalid file name: " << strFileName << " error = " << Result;
        return false;
    }

    // Get an IShellFolder for the folder
    // the file is located in.
    CComWrapper<IShellFolder> ParentFolder;
    Result = m_DesktopFolder.Get()->BindToObject( ParentPidl, 0, IID_IShellFolder, (void**)ParentFolder.Set() );
    m_Malloc.Get()->Free( ParentPidl );
    if( NULL == ParentFolder.Get() )
    {
        CLog( Debug ) << "CContextMenu::GetUIObjectOfFile: Invalid file name: " << strFileName;
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
        CLog( Debug ) << "CContextMenu::GetUIObjectOfFile: Unable to get context menu interface for " << strFileName;
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
    if( GetUIObjectOfFile( strFileName, Pcm ) )
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
    if( g_Pcm3.Get() )
    {
        LRESULT lres;
        if( SUCCEEDED( g_Pcm3.Get()->HandleMenuMsg2( message, wParam, lParam, &lres ) ) )
            return lres;
    }
    else if( g_Pcm2.Get() )
        if( SUCCEEDED( g_Pcm2.Get()->HandleMenuMsg( message, wParam, lParam ) ) )
            return 0;
    return ::CallWindowProc( g_OldWndProc, hWnd, message, wParam, lParam );
}
#endif


