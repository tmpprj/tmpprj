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
{
    setupUi( this );

    setupProgressAnimation();
    setupControls();
    connectSearcher();
    connectWidgets();
    showDefaultStatus();
    startStatusUpdateTimer();

    reloadSettings();
    CLog(debug) << "GUI THREAD: " << QThread::currentThreadId() << std::endl;
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
}

void QSearchWindow::connectSearcher()
{
    connect( &m_search, SIGNAL( fileProcessing( const QString& ) ), 
            this, SLOT( fileProcessing( const QString& ) ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( fileMatched( const QString& ) ), 
            this, SLOT( fileMatched( const QString& ) ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( searchDone() ), this, SLOT( searchDone() ), Qt::QueuedConnection );
    connect( &m_search, SIGNAL( error( const QString&, const QString& ) ),
            this, SLOT( searchError( const QString&, const QString& ) ), Qt::QueuedConnection );
}

void QSearchWindow::connectWidgets()
{
    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
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
    statusBar()->showMessage( "Status: Ready" );
}

void QSearchWindow::showSearchStatus( const QString& strFilename )
{
    statusBar()->showMessage( "Searching: " + strFilename );
}

void QSearchWindow::saveCurrentUIItems()
{
    MoveCurrentToTop( masksComboBox );
    MoveCurrentToTop( textComboBox );
    MoveCurrentToTop( directoryComboBox );
}

void QSearchWindow::closeEvent( QCloseEvent* )
{
    // disconnect all searcher signals to not receive signal after form closed
    disconnect( &m_search, 0, 0, 0 );
}

void QSearchWindow::browse()
{
    QString strBrowseDir = directoryComboBox->currentText();
    if( strBrowseDir.isEmpty() )
        strBrowseDir = QDir::currentPath();

    QString directory = QFileDialog::getExistingDirectory( this, tr( "Find Files" ), strBrowseDir );
    if( !directory.isEmpty() ) 
    {
        directoryComboBox->insertItem( 0, directory );
        directoryComboBox->setCurrentIndex( 0 );
    }
}

void QSearchWindow::fileProcessing( const QString& strFilename )
{
    CLog(debug) << __FUNCTION__ << ": " << qPrintable( strFilename ) << std::endl;
    m_strCurrentFile = strFilename;
}

void QSearchWindow::fileMatched( const QString& strFilename )
{
    CLog(debug) << __FUNCTION__ << ": " << qPrintable( strFilename ) << std::endl;

    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), "FOUND" );
}

void QSearchWindow::searchDone()
{
    CLog(debug) << __FUNCTION__;
    m_progressMovie.stop();
    m_strCurrentFile.clear();
}

void QSearchWindow::searchError( const QString& strFilename, const QString& strError )
{
    filesTable->AddFile( QDir::toNativeSeparators( strFilename ), strError, Qt::red );
}

void QSearchWindow::find()
{
    stop();
    saveCurrentUIItems();
   
    filesTable->ClearList();

    QString strMasks = masksComboBox->currentText();
    QString strText = textComboBox->currentText();
    bool bCaseSensitive = ( caseCheckBox->checkState() == Qt::Checked );
    bool bRecursive = ( recursiveCheckBox->checkState() == Qt::Checked );
    QString strPath = directoryComboBox->currentText();

    QStringList listPatterns;
    ParsePatterns( strText, listPatterns );
   
    QStringList listMasks;
    ParseMasks( strMasks, listMasks );

    SearchOptions options = { strPath, listPatterns, listMasks, bCaseSensitive, bRecursive };
    options.strPath = strPath;

    m_search.GetSearcher().Start( options );
    m_progressMovie.start();
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
    LoadStringListToCombo( masksComboBox, SearchGUI::Conf().listMasks.Value(), "*" );
    LoadStringListToCombo( textComboBox, SearchGUI::Conf().listSearches.Value() );
    LoadStringListToCombo( directoryComboBox, SearchGUI::Conf().listSearchPaths.Value(), QDir::currentPath() );

    reloadExtensions();
}

void QSearchWindow::saveSettings()
{
    SearchGUI::Conf().bCaseSensitive.Value() = ( caseCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().bRecursive.Value() = ( recursiveCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().listMasks.Value() = GetComboStringList( masksComboBox, true );
    SearchGUI::Conf().listSearches.Value() = GetComboStringList( textComboBox, true );
    SearchGUI::Conf().listSearchPaths.Value() = GetComboStringList( directoryComboBox, true );
}

void QSearchWindow::updateTimer()
{
    if( m_strCurrentFile.isEmpty() )
        showDefaultStatus();
    else
        showSearchStatus( m_strCurrentFile ); 
}
