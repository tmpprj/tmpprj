#include <QtGui>
#include <QtCore>

#include "qsearchwindow.h"
#include "qfilestable.h"
#include "qsettingswindow.h"
#include "qjournalwindow.h"
#include "settings.h"
#include "searchgui_conf.h"
#include "guicommon.h"

#include <log.hpp>
#include <macro.h>

using namespace std;

QSearchWindow::QSearchWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi( this );
    setWindowTitle( tr( "Find Files" ) );

    setupProgressAnimation();
    setupControls();
    connectSearcher();
    connectWidgets();

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
    connect( &m_search, SIGNAL( searchDone() ), this, SLOT( searchDone() ) );
    connect( &m_search, SIGNAL( fileMatched( const QString&, bool ) ), 
            this, SLOT( fileMatched( const QString&, bool ) ) );
}

void QSearchWindow::connectWidgets()
{
    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( settingsButton, SIGNAL( clicked() ), this, SLOT( showSettings() ) );
    connect( journalButton, SIGNAL( clicked() ), this, SLOT( showJournal() ) );
    connect( this, SIGNAL( finished( int ) ), this, SLOT( closing() ) );
}

void QSearchWindow::acceptCurrentItems()
{
    MoveCurrentToTop( masksComboBox );
    MoveCurrentToTop( textComboBox );
    MoveCurrentToTop( directoryComboBox );
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
    if( bFound )
        filesTable->AddFile( strFilename );
}

void QSearchWindow::searchDone()
{
    m_progressMovie.stop();
}

void QSearchWindow::find()
{
    stop();
    acceptCurrentItems();
   
    filesTable->ClearList();

    QString strMasks = masksComboBox->currentText();
    QString strText = textComboBox->currentText();
    bool bCaseSensitive = ( caseCheckBox->checkState() == Qt::Checked );
    QString strPath = directoryComboBox->currentText();

    QStringList listPatterns;
    ParsePatterns( strText, listPatterns );
   
    QStringList listMasks = strMasks.split( ";", QString::SkipEmptyParts );

    m_search.GetSearcher().Start( strPath, listPatterns, listMasks, bCaseSensitive );
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

void QSearchWindow::showJournal()
{
    QJournalWindow* pJournal = new QJournalWindow( this );
    pJournal->show();
}

void QSearchWindow::reloadExtensions()
{
    TextExtractorFactory::Instance().ClearExtensions();

    FOREACH( p, SearchGUI::Conf().extensions )
        TextExtractorFactory::Instance().RegisterExtension( qPrintable( "." + p.key() ), 
                qPrintable( p.value().toString() ) );
}

void QSearchWindow::reloadSettings()
{
    caseCheckBox->setCheckState( SearchGUI::Conf().bCaseSensitive ? Qt::Checked : Qt::Unchecked );
    LoadStringListToCombo( masksComboBox, SearchGUI::Conf().masks );
    if( masksComboBox->count() == 0 )
        masksComboBox->addItem( "*" );
    
    LoadStringListToCombo( textComboBox, SearchGUI::Conf().searches );
    
    LoadStringListToCombo( directoryComboBox, SearchGUI::Conf().searchPaths );
    if( directoryComboBox->count() == 0 )
        directoryComboBox->addItem( QDir::currentPath() );

    reloadExtensions();
}

void QSearchWindow::saveSettings()
{
    SearchGUI::Conf().bCaseSensitive = ( caseCheckBox->checkState() == Qt::Checked );
    SearchGUI::Conf().masks = GetComboStringList( masksComboBox, true );
    SearchGUI::Conf().searches = GetComboStringList( textComboBox, true );
    SearchGUI::Conf().searchPaths = GetComboStringList( directoryComboBox, true );
}

void QSearchWindow::closing()
{
    // disconnect all searcher signals to not receive signal after form closed
    disconnect( &m_search, 0, 0, 0 );
}

