#include <contextmenu.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>
#include <boost/filesystem.hpp>
#include <boost/concept_check.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#ifdef WIN32
IContextMenu2 *g_pcm2;
IContextMenu3 *g_pcm3;
boost::mutex g_mtx;
#endif

CContextMenu::CContextMenu( WId WinId ):m_WinId( WinId )
{
#ifdef WIN32
    // Get an IShellFolder for the desktop.
    SHGetDesktopFolder( &m_DesktopFolder );
    if( NULL == m_DesktopFolder )
        QMessageBox::warning( NULL, "test", "!m_DesktopFolder" );
#endif
}

void CContextMenu::Show( QPoint ptWhere, QString strFileName )
{
#ifdef WIN32
    boost::filesystem::path pathFile( strFileName.toStdString() );
    // Get a pidl for the folder the file
    // is located in.
    wchar_t Path[MAX_PATH];
    ::memset( Path, 0, sizeof(Path) );
    LPITEMIDLIST ParentPidl;
    DWORD Eaten;
    QString::fromStdString( pathFile.parent_path().directory_string() ).toWCharArray( Path );
    DWORD Result = m_DesktopFolder->ParseDisplayName( m_WinId, 0, Path, &Eaten, &ParentPidl, 0);
    if( Result != NOERROR )
    {
        QMessageBox::warning( NULL, QString::number( Result ), "Invalid file name." );
        return;
    }

    // Get an IShellFolder for the folder
    // the file is located in.
    LPSHELLFOLDER ParentFolder;
    Result = m_DesktopFolder->BindToObject( ParentPidl, 0, IID_IShellFolder, (void**)&ParentFolder );
    if( NULL == ParentFolder )
    {
        QMessageBox::warning( NULL, "test", "Invalid file name." );
        return;
    }

    // Get a pidl for the file itself.
    LPITEMIDLIST Pidl;
    ::memset( Path, 0, sizeof(Path) );
    QString::fromStdString( pathFile.filename() ).toWCharArray( Path );
    ParentFolder->ParseDisplayName( m_WinId, 0, Path, &Eaten, &Pidl, 0 );

    // Get the IContextMenu for the file.
    LPCONTEXTMENU CM;
    ParentFolder->GetUIObjectOf( m_WinId, 1, (LPCITEMIDLIST*)&Pidl, IID_IContextMenu, 0, (void**)&CM );

    if (!CM)
    {
        QMessageBox::warning( NULL, "test", "Unable to get context menu interface." );
        return;
    }

    HMENU hMenu = CreatePopupMenu();
    DWORD Flags = CMF_EXPLORE; //CMF_NORMAL?
#define SCRATCH_QCM_FIRST 1
#define SCRATCH_QCM_LAST  0x7FFF
    CM->QueryContextMenu( hMenu, 0, SCRATCH_QCM_FIRST, SCRATCH_QCM_LAST, Flags );

    CM->QueryInterface(IID_IContextMenu2, (void**)&g_pcm2);
    CM->QueryInterface(IID_IContextMenu3, (void**)&g_pcm3);

    // subclass window to handle menurelated messages in CShellContextMenu
    WNDPROC OldWndProc;
    if( NULL != g_pcm2 || NULL != g_pcm3 )
        OldWndProc = (WNDPROC)SetWindowLong( m_WinId, GWL_WNDPROC, (DWORD)HookWndProc );
    else
        OldWndProc = NULL;

    int Cmd = TrackPopupMenuEx(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, ptWhere.x(), ptWhere.y(), m_WinId, 0 );
    if(OldWndProc) // unsubclass
        SetWindowLong( m_WinId, GWL_WNDPROC, (DWORD) OldWndProc );


    if (g_pcm2) {
        g_pcm2->Release();
        g_pcm2 = NULL;
    }
    if (g_pcm3) {
        g_pcm3->Release();
        g_pcm3 = NULL;
    }
    if (Cmd < 100 && Cmd != 0)
    {
        CMINVOKECOMMANDINFO info = { 0 };
        info.cbSize = sizeof(info);
        info.hwnd = m_WinId;
        info.lpVerb  = MAKEINTRESOURCEA(Cmd - SCRATCH_QCM_FIRST);
        info.nShow = SW_SHOWNORMAL;
        //        CI.lpParameters = "";
        //        CI.lpDirectory = "";
        CM->InvokeCommand(&info);
    }
    DestroyMenu(hMenu);
    CM->Release();
#else
    boost::ignore_unused_variable_warning( strFileName );
    boost::ignore_unused_variable_warning( ptWhere );
#endif
}

void CContextMenu::InvokeDefault( QString strFileName )
{
#ifdef WIN32
#else
    boost::ignore_unused_variable_warning( strFileName );
#endif
}

#ifdef WIN32

LRESULT CALLBACK CContextMenu::HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    boost::unique_lock<boost::mutex> lock( g_mtx );
    if (g_pcm3)
    {
        LRESULT lres;
        if( SUCCEEDED( g_pcm3->HandleMenuMsg2( message, wParam, lParam, &lres ) ) )
            return lres;
    }
    else if( g_pcm2 )
        if( SUCCEEDED( g_pcm2->HandleMenuMsg( message, wParam, lParam ) ) )
            return 0;
    return ::CallWindowProc((WNDPROC) GetProp ( hWnd, TEXT ("OldWndProc")), hWnd, message, wParam, lParam);
}
#endif


