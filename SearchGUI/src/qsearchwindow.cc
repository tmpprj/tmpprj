#include <QtGui>
#include <QtCore>

#include "qsearchwindow.h"
#include "qfilestable.h"
#include "qsettingswindow.h"
#include "settings.h"
#include "searchgui_conf.h"
#include "guicommon.h"

#include <log.h>
#include <macro.h>

using namespace std;

QSearchWindow::QSearchWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tTimeElapsed( 0 )
    , m_status( SS_READY )
{
    setupUi( this );

    setupProgressAnimation();
    setupControls();
    setupTrayIcon();
    connectSearcher();
    connectWidgets();
    showReadyStatus();
    startStatusUpdateTimer();

    reloadSettings();
    CLog(Debug) << "GUI THREAD: " << QThread::currentThreadId();
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

    connect( masksComboBox, SIGNAL( editTextChanged(QString) ), this, SLOT(validateInputData()) );
    connect( textComboBox, SIGNAL( editTextChanged(QString) ), this, SLOT(validateInputData()) );
    connect( directoryComboBox, SIGNAL( editTextChanged(QString) ), this, SLOT(validateInputData()) );

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
            this, SLOT( fileProcessing( const QString& ) ), Qt::BlockingQueuedConnection );
    connect( &m_search, SIGNAL( fileMatched( const QString& ) ), 
            this, SLOT( fileMatched( const QString& ) ), Qt::BlockingQueuedConnection );
    connect( &m_search, SIGNAL( searchStart() ), this, SLOT( searchStart() ), Qt::BlockingQueuedConnection );
    connect( &m_search, SIGNAL( searchDone() ), this, SLOT( searchDone() ), Qt::BlockingQueuedConnection );
    connect( &m_search, SIGNAL( error( const QString&, const QString& ) ),
            this, SLOT( searchError( const QString&, const QString& ) ), Qt::BlockingQueuedConnection );
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

    timer->setInterval( 10 );
    timer->start();
}

void QSearchWindow::showStatus( const QString& strState )
{
    QString strStatus = "Status: " + strState;
    if( !m_SearchTimerStart.isNull() && 0 != m_tTimeElapsed )
        strStatus += ".   Time elapsed: " + QString::number( m_tTimeElapsed/1000 ) + 
            " sec.   Files processed: " + QString::number( m_stFilesProcessed ) +
            ".   Files matched: " + QString::number( m_stFilesMatched );

    setStatus( strStatus );
}

void QSearchWindow::showReadyStatus()
{
    showStatus( "Ready" );
}

void QSearchWindow::showToManyFilesStatus()
{
    showStatus( "Too many files matched" );
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
        directoryComboBox->PushTextToList( directory );
}

void QSearchWindow::fileProcessing( const QString& strFilename )
{
    CLog(Debug) << __FUNCTION__ << ": " << qPrintable( strFilename );
    m_strCurrentFile = strFilename;
    ++m_stFilesProcessed;
}

void QSearchWindow::fileMatched( const QString& strFilename )
{
    CLog(Debug) << __FUNCTION__ << ": " << qPrintable( strFilename );

    if( filesTable->rowCount() >= SearchGUI::Conf().nMaxFiles.Value() )
    {
        m_status = SS_TOOMANYFILES;
        stop();
    }

    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), "FOUND" );
    
    ++m_stFilesMatched;
}

void QSearchWindow::searchStart()
{
    CLog( Debug ) << __FUNCTION__;
    m_progressMovie.start();
    m_status = SS_SEARCHING;
}

void QSearchWindow::searchDone()
{
    CLog( Debug ) << __FUNCTION__;
    m_progressMovie.stop();
    m_strCurrentFile.clear();
    m_tTimeElapsed = m_SearchTimerStart.elapsed();

    if( m_status == SS_SEARCHING )
    {
        m_TrayIcon.showMessage( "Search done!", QString::number( m_stFilesMatched ) + " files matched." );
        m_status = SS_READY;
    }
    else if( m_status == SS_TOOMANYFILES )
        m_TrayIcon.showMessage( "Search done!", "Too many files matched" );
}

void QSearchWindow::searchError( const QString& strFilename, const QString& strError )
{
    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), strError, Qt::red );
}

void QSearchWindow::validateInputData()
{
    if( masksComboBox->GetCurrentText().isEmpty() 
        || directoryComboBox->GetCurrentText().isEmpty() )
    {
        findButton->setEnabled( false );
    }
    else
        findButton->setEnabled( true );
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

    CLog( Debug ) << "Masks : " << qPrintable( strMasks );
    CLog( Debug ) << "Text : " << qPrintable( strText );

    QStringList listPatterns;
    ParsePatterns( strText, listPatterns );
   
    QStringList listMasks;
    ParseMasks( strMasks, listMasks );

    SearchOptions options = { strPath, listPatterns, listMasks, bCaseSensitive, bRecursive, 
        groupFileSize->isChecked() ? lineMinFileSize->text().toULongLong() : 0, 
        groupFileSize->isChecked() ? lineMaxFileSize->text().toULongLong() : 0, 
        charsetCheckBox->isChecked() };

    m_search.Start( options );
    m_SearchTimerStart = QTime::currentTime();
    m_stFilesProcessed = 0;
    m_stFilesMatched = 0;
}

void QSearchWindow::stop()
{
    m_search.Stop();
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

    groupFileSize->setChecked( SearchGUI::Conf().bFileSizeLimits.Value() );
    lineMinFileSize->setText( QString::number( SearchGUI::Conf().ullMinFileSize.Value() ) );
    lineMaxFileSize->setText( QString::number( SearchGUI::Conf().ullMaxFileSize.Value() ) );
    charsetCheckBox->setChecked( SearchGUI::Conf().bCharsetDetect.Value() );

    reloadExtensions();
}

void QSearchWindow::saveSettings()
{
    SearchGUI::Conf().bCaseSensitive.Value() = ( caseCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().bRecursive.Value() = ( recursiveCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().listMasks.Value() = masksComboBox->GetFullElements();
    SearchGUI::Conf().listSearches.Value() = textComboBox->GetFullElements();
    SearchGUI::Conf().listSearchPaths.Value() = directoryComboBox->GetFullElements();
    SearchGUI::Conf().bFileSizeLimits.Value() = groupFileSize->isChecked();
    SearchGUI::Conf().ullMinFileSize.Value() = lineMinFileSize->text().toULongLong();
    SearchGUI::Conf().ullMaxFileSize.Value() = lineMaxFileSize->text().toULongLong();
    SearchGUI::Conf().bCharsetDetect.Value() = charsetCheckBox->isChecked();
}

void QSearchWindow::updateTimer()
{
    switch( m_status )
    {
        case SS_READY:
            showReadyStatus();
            break;
        case SS_SEARCHING:
            showSearchStatus( m_strCurrentFile ); 
            break;
        case SS_TOOMANYFILES:
            showToManyFilesStatus();
            break;
    }
}

