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

    reloadSettings();
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
    completer->setModel( new QDirModel( completer ) );
    directoryComboBox->setCompleter( completer );
    directoryComboBox->setInsertPolicy( QComboBox::NoInsert );
}

void QSearchWindow::connectSearcher()
{
    connect( &m_search, SIGNAL( fileMatched( const QString&, bool ) ), 
            this, SLOT( fileMatched( const QString&, bool ) ) );
    connect( &m_search, SIGNAL( searchDone() ), this, SLOT( searchDone() ) );
    connect( &m_search, SIGNAL( error( const QString&, const QString& ) ),
            this, SLOT( searchError( const QString&, const QString& ) ) );
}

void QSearchWindow::connectWidgets()
{
    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( settingsButton, SIGNAL( clicked() ), this, SLOT( showSettings() ) );
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

void QSearchWindow::fileMatched( const QString& strFilename, bool bFound )
{
    CLog(debug) << __FUNCTION__ << std::endl;
    showSearchStatus( strFilename );

    if( bFound )
        filesTable->AddFile( QDir::toNativeSeparators( strFilename ), "FOUND" );
}

void QSearchWindow::searchDone()
{
    CLog(debug) << __FUNCTION__ << std::endl;
    m_progressMovie.stop();
    showDefaultStatus();
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

