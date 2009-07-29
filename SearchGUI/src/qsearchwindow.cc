#include <QtGui>
#include <QtCore>

#include "qsearchwindow.h"
#include "qfilestable.h"
#include "qsettingswindow.h"
#include "settings.h"
#include "searchgui_conf.h"
#include "guicommon.h"

#include <log.hpp>
#include <macro.h>

using namespace std;

QSearchWindow::QSearchWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tTimeElapsed(0)
{
    setupUi( this );

    setupProgressAnimation();
    setupControls();
    setupTrayIcon();
    connectSearcher();
    connectWidgets();
    showDefaultStatus();
    startStatusUpdateTimer();

    reloadSettings();
    CLog(debug) << "GUI THREAD: " << QThread::currentThreadId();
}

QSearchWindow::~QSearchWindow()
{
    saveSettings();
}

void QSearchWindow::setupProgressAnimation()
{
    m_progressMovie.setFileName( ":/animation/progress.gif" );
    progressLabel->setMovie( &m_progressMovie );
    m_progressMovie.jumpToNextFrame();
}

void QSearchWindow::setupControls()
{
    masksComboBox->setInsertPolicy( QComboBox::NoInsert );
    textComboBox->setInsertPolicy( QComboBox::NoInsert );
    
    QCompleter *completer = new QCompleter( this );
    QDirModel* model = new QDirModel( completer );
    model->setFilter( QDir::AllDirs | QDir::Drives | QDir::NoDotAndDotDot );
    model->setSorting( QDir::Name );
    completer->setModel( model );
    
    directoryComboBox->setCompleter( completer );
    directoryComboBox->setInsertPolicy( QComboBox::NoInsert );
    directoryComboBox->SetDefaultElement( QDir::currentPath() );

    QValidator* pValidatorMin = new QIntValidator( 0, 999999999LL, this );
    lineMinFileSize->setValidator( pValidatorMin );
    QValidator* pValidatorMax = new QIntValidator( 1, 999999999LL, this );
    lineMaxFileSize->setValidator( pValidatorMax );
}

void QSearchWindow::setupTrayIcon()
{
    m_TrayIcon.setIcon( QIcon(":/icons/icon1.gif") );
    connect( &m_TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT( maximazeFromTray( ) ) ); 
    connect( &m_TrayIcon, SIGNAL(messageClicked()), this, SLOT( maximazeFromTray( ) ) ); 
}

void QSearchWindow::connectSearcher()
{
    connect( &m_search, SIGNAL( fileProcessing( const QString& ) ), 
            this, SLOT( fileProcessing( const QString& ) ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( fileMatched( const QString& ) ), 
            this, SLOT( fileMatched( const QString& ) ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( searchStart() ), this, SLOT( searchStart() ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( searchDone() ), this, SLOT( searchDone() ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( error( const QString&, const QString& ) ),
            this, SLOT( searchError( const QString&, const QString& ) ), Qt::QueuedConnection );
}

void QSearchWindow::connectWidgets()
{
    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
    connect( hideButton, SIGNAL( clicked() ), this, SLOT( minimazeToTray() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( settingsButton, SIGNAL( clicked() ), this, SLOT( showSettings() ) );
}

void QSearchWindow::startStatusUpdateTimer()
{
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( updateTimer() ) );

    timer->setInterval( 100 );
    timer->start();
}

void QSearchWindow::showDefaultStatus()
{
    QString strStatus = "Status: Ready";
    if( !m_SearchTimerStart.isNull() && 0 != m_tTimeElapsed )
        strStatus += ".   Time elapsed: " + QString::number( m_tTimeElapsed/1000 ) + 
            " sec.   Files processed: " + QString::number( m_stFilesProcessed ) +
            ".   Files matched: " + QString::number( m_stFilesMatched );

    setStatus( strStatus );
}

void QSearchWindow::showSearchStatus( const QString& strFilename )
{
    setStatus( "Searching: " + strFilename );
}

void QSearchWindow::saveCurrentUIItems()
{
    masksComboBox->PushCurrentToList();
    textComboBox->PushCurrentToList();
    directoryComboBox->PushCurrentToList();
}

void QSearchWindow::closeEvent( QCloseEvent* )
{
    // disconnect all searcher signals to not receive signal after form closed
    disconnect( &m_search, 0, 0, 0 );
}

void QSearchWindow::setStatus( const QString& strStatus )
{
    statusBar()->showMessage( strStatus );
    m_TrayIcon.setToolTip( strStatus );
}

void QSearchWindow::browse()
{
    QString strBrowseDir = directoryComboBox->GetCurrentText();
    if( strBrowseDir.isEmpty() )
        strBrowseDir = QDir::currentPath();

    QString directory = QFileDialog::getExistingDirectory( this, tr( "Find Files" ), strBrowseDir, 
            QFileDialog::DontUseNativeDialog | QFileDialog::ShowDirsOnly );
    if( !directory.isEmpty() ) 
    {
        directoryComboBox->insertItem( 0, directory );
        directoryComboBox->setCurrentIndex( 0 );
    }
}

void QSearchWindow::fileProcessing( const QString& strFilename )
{
    CLog(debug) << __FUNCTION__ << ": " << qPrintable( strFilename );
    m_strCurrentFile = strFilename;
    ++m_stFilesProcessed;
}

void QSearchWindow::fileMatched( const QString& strFilename )
{
    CLog(debug) << __FUNCTION__ << ": " << qPrintable( strFilename );

    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), "FOUND" );
    
    ++m_stFilesMatched;
}

void QSearchWindow::searchStart()
{
    CLog( debug ) << __FUNCTION__;
    m_progressMovie.start();
}

void QSearchWindow::searchDone()
{
    CLog( debug ) << __FUNCTION__;
    m_progressMovie.stop();
    m_strCurrentFile.clear();
    m_tTimeElapsed = m_SearchTimerStart.elapsed();
    m_TrayIcon.showMessage( "Notification message", "Search done!" );
}

void QSearchWindow::searchError( const QString& strFilename, const QString& strError )
{
    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), strError, Qt::red );
}

void QSearchWindow::minimazeToTray()
{
    m_TrayIcon.show();
    hide();
}

void QSearchWindow::maximazeFromTray()
{
    show();
    m_TrayIcon.hide();
}

void QSearchWindow::find()
{
    stop();
    saveCurrentUIItems();
   
    filesTable->ClearList();

    QString strMasks = masksComboBox->GetCurrentText();
    QString strText = textComboBox->GetCurrentText();
    bool bCaseSensitive = ( caseCheckBox->checkState() == Qt::Checked );
    bool bRecursive = ( recursiveCheckBox->checkState() == Qt::Checked );
    QString strPath = directoryComboBox->GetCurrentText();

    CLog( debug ) << "Masks : " << qPrintable( strMasks );
    CLog( debug ) << "Text : " << qPrintable( strText );

    QStringList listPatterns;
    ParsePatterns( strText, listPatterns );
   
    QStringList listMasks;
    ParseMasks( strMasks, listMasks );

    SearchOptions options = { strPath, listPatterns, listMasks, bCaseSensitive, bRecursive, groupFileSize->isChecked() ? lineMinFileSize->text().toULongLong() : 0, groupFileSize->isChecked() ? lineMaxFileSize->text().toULongLong() : 0 };

    m_search.GetSearcher().Start( options );
    m_SearchTimerStart = QTime::currentTime();
    m_stFilesProcessed = 0;
    m_stFilesMatched = 0;
}

void QSearchWindow::stop()
{
    m_search.GetSearcher().Stop();
}

void QSearchWindow::showSettings()
{
    QSettingsWindow* pSettings = new QSettingsWindow( this );
    connect( pSettings, SIGNAL( settingsChanged() ), this, SLOT( reloadExtensions() ) ); 
    pSettings->setModal( true );
    pSettings->show();
}

void QSearchWindow::reloadExtensions()
{
    TextExtractorFactory::Instance().ClearExtensions();

    FOREACH( p, SearchGUI::Conf().mapExtensions.Value() )
        TextExtractorFactory::Instance().RegisterExtension( p.key(), p.value().toString() );
}

void QSearchWindow::reloadSettings()
{
    caseCheckBox->setCheckState( SearchGUI::Conf().bCaseSensitive.Value() ? Qt::Checked : Qt::Unchecked );
    recursiveCheckBox->setCheckState( SearchGUI::Conf().bRecursive.Value() ? Qt::Checked : Qt::Unchecked );
    
    masksComboBox->SetFullElements( SearchGUI::Conf().listMasks.Value() );
    textComboBox->SetFullElements( SearchGUI::Conf().listSearches.Value() );
    directoryComboBox->SetFullElements( SearchGUI::Conf().listSearchPaths.Value() );

    reloadExtensions();
}

void QSearchWindow::saveSettings()
{
    SearchGUI::Conf().bCaseSensitive.Value() = ( caseCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().bRecursive.Value() = ( recursiveCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().listMasks.Value() = masksComboBox->GetFullElements();
    SearchGUI::Conf().listSearches.Value() = textComboBox->GetFullElements();
    SearchGUI::Conf().listSearchPaths.Value() = directoryComboBox->GetFullElements();
}

void QSearchWindow::updateTimer()
{
    if( m_strCurrentFile.isEmpty() )
        showDefaultStatus();
    else
        showSearchStatus( m_strCurrentFile ); 
}

