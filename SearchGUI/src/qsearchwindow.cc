#include <QtGui>
#include <QtCore>
#include <boost/foreach.hpp>

#include "qsearchwindow.h"
#include "qfilestable.h"
#include "qsettingswindow.h"
#include "qjournalwindow.h"
#include "settings.h"
#include "searchgui_conf.h"
#include "guicommon.h"

#include <log.hpp>

using namespace std;

QSearchWindow::QSearchWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi( this );
    setWindowTitle( tr( "Find Files" ) );

    m_progressMovie.setFileName( ":/animation/progress.gif" );
    progressLabel->setMovie( &m_progressMovie );
    m_progressMovie.jumpToNextFrame();

    QCompleter *completer = new QCompleter( this );
    completer->setModel( new QDirModel( completer ) );
    directoryComboBox->setCompleter( completer );

    m_search.SigFileMatched().connect( boost::bind( &QSearchWindow::OnFileMatched, this, _1 ) );
    m_search.SigFileProcessed().connect( boost::bind( &QSearchWindow::OnFileProcessed, this, _1 ) );
    m_search.SigFileFound().connect( boost::bind( &QSearchWindow::OnFileFound, this, _1 ) );
    m_search.SigSearchDone().connect( boost::bind( &QSearchWindow::OnSearchDone, this ) );

    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( settingsButton, SIGNAL( clicked() ), this, SLOT( showSettings() ) );
    connect( journalButton, SIGNAL( clicked() ), this, SLOT( showJournal() ) );
    connect( this, SIGNAL( finished( int ) ), this, SLOT( closing() ) );

    reloadSettings();
    if( directoryComboBox->count() == 0 )
        directoryComboBox->addItem( QDir::currentPath() );
}

QSearchWindow::~QSearchWindow()
{
    PutCurrentTextsInCombo();
    SaveSettingsTextCombo();
    SaveSettingsFoldersCombo();
}

void QSearchWindow::PutCurrentTextsInCombo()
{
    ComboInsertCurrentToTop( textComboBox );
    ComboInsertCurrentToTop( directoryComboBox );
}

void QSearchWindow::SaveSettingsTextCombo()
{
    SearchGUI::Conf().searches = GetComboStringList( textComboBox );
}

void QSearchWindow::SaveSettingsFoldersCombo()
{
    SearchGUI::Conf().searchPaths = GetComboStringList( directoryComboBox );
}

void QSearchWindow::OnFileMatched( const CPatternMatcher::structFindData& Data )
{
    if( Data.bFound )
        filesTable->AddFile( Data.strFileName );
}

void QSearchWindow::OnFileProcessed( const CPlainTextExtractor::structFileData& )
{
}

void QSearchWindow::OnFileFound( const QString& )
{
}

void QSearchWindow::OnSearchDone()
{
    m_progressMovie.stop();
}

void QSearchWindow::browse()
{
    QString strBrowseDir = directoryComboBox->currentText();
    if( strBrowseDir.isEmpty() )
        strBrowseDir = QDir::currentPath();

    QString directory = QFileDialog::getExistingDirectory(this,
                            tr( "Find Files" ), strBrowseDir );
    if (!directory.isEmpty()) 
    {
        directoryComboBox->addItem( directory );
        directoryComboBox->setCurrentIndex( directoryComboBox->count() - 1 );

        SaveSettingsFoldersCombo();
    }
}

void AddPattern( PatternsContainer& patterns, const QString& strText )
{
    if( strText.isEmpty() )
        return;

    CLog() << "PATTERN: " << qPrintable( strText ) << std::endl;
    patterns.push_back( std::string( ( const char* )strText.unicode(), strText.size() * sizeof( QChar ) ) );
}

void ParsePatterns( const QString& text, PatternsContainer& patterns )
{
    int nStart = 0;
    bool bCommaBlock = false;

    for( int i = 0; i <= text.size(); i++ )
        if( i == text.size() )
        {
            if( !bCommaBlock )
                AddPattern( patterns, text.mid( nStart, i - nStart ).trimmed() );
        }
        else if( text[ i ] == '"' )
        {
            if( bCommaBlock )
                AddPattern( patterns, text.mid( nStart, i - nStart ).trimmed() );

            bCommaBlock = !bCommaBlock;
            nStart = i + 1;
        }
        else if( text[ i ] == ' ' )
        {
            if( !bCommaBlock )
            {
                AddPattern( patterns, text.mid( nStart, i - nStart ).trimmed() );
                nStart = i + 1;
            }
        }
}

void QSearchWindow::find()
{
    PutCurrentTextsInCombo();
    
    m_search.Stop();
    filesTable->ClearList();

    QString fileName = "*";//fileComboBox->currentText();
    QString text = textComboBox->currentText();
    QString path = directoryComboBox->currentText();

    PatternsContainer patterns;
    ParsePatterns( text, patterns );
   
    Masks_t masks;
    QStringList listMasks = fileName.split( ";", QString::SkipEmptyParts );

    for( int i = 0; i < listMasks.size(); i++ )
        masks.push_back( qPrintable( listMasks[ i ].trimmed() ) );

    m_search.Start( qPrintable( path ), patterns, masks );
    m_progressMovie.start();
}

void QSearchWindow::stop()
{
    m_search.Stop();
}

void QSearchWindow::showSettings()
{
    QSettingsWindow* pSettings = new QSettingsWindow( this );
    connect( pSettings, SIGNAL( settingsChanged() ), this, SLOT( reloadExtensions() ) ); 
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

    typedef QMap< QString, QVariant >::iterator ExtensionsMappedType_t;
    for( ExtensionsMappedType_t p = SearchGUI::Conf().extensions.begin();
            p != SearchGUI::Conf().extensions.end(); p++ )
        TextExtractorFactory::Instance().RegisterExtension( qPrintable( "." + p.key() ), 
                qPrintable( p.value().toString() ) );
}

void QSearchWindow::reloadSettings()
{
    BOOST_FOREACH( QString str, SearchGUI::Conf().searches )
        if( !str.isEmpty() )
            textComboBox->addItem( str );
    BOOST_FOREACH( QString str, SearchGUI::Conf().searchPaths )
        if( !str.isEmpty() )
            directoryComboBox->addItem( str );
    reloadExtensions();
}

void QSearchWindow::closing()
{
    // disconnect done signal to not receive signal after form closed
    m_search.SigSearchDone().disconnect( boost::bind( &QSearchWindow::OnSearchDone, this ) );
}

