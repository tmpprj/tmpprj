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

    QCompleter *completer = new QCompleter( this );
    completer->setModel( new QDirModel( completer ) );
    directoryComboBox->setCompleter( completer );

    m_search.SigFileMatched().connect( boost::bind( &QSearchWindow::FileMatched, this, _1, _2 ) );
    m_search.SigFileProcessed().connect( boost::bind( &QSearchWindow::FileProcessed, this, _1, _2 ) );
    m_search.SigFileFound().connect( boost::bind( &QSearchWindow::FileFound, this, _1 ) );

    connect( findButton, SIGNAL( clicked() ), this, SLOT( find() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stop() ) );
    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( settingsButton, SIGNAL( clicked() ), this, SLOT( showSettings() ) );
    connect( journalButton, SIGNAL( clicked() ), this, SLOT( showJournal() ) );

    reloadSettings();
    if( directoryComboBox->count() == 0 )
        directoryComboBox->addItem( QDir::currentPath() );
}

QSearchWindow::~QSearchWindow()
{
    SaveSettingsTextCombo();
    SaveSettingsFoldersCombo();
}

void QSearchWindow::SaveSettingsTextCombo()
{
    SearchGUI::Conf().searches = GetComboStringList( textComboBox );
}

void QSearchWindow::SaveSettingsFoldersCombo()
{
    SearchGUI::Conf().searchPaths = GetComboStringList( directoryComboBox );
}

void QSearchWindow::FileMatched( const std::string& strFilename, bool bMatchOk )
{
    if( bMatchOk )
        filesTable->AddFile( strFilename.c_str() );
}

void QSearchWindow::FileProcessed( const std::string& strFilename, const QString& )
{
    CLog() << debug << "FileProcessed: " << strFilename << endl;
}

void QSearchWindow::FileFound( const std::string& strFilename )
{
    CLog() << debug << "FileFound: " << strFilename << endl;
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

void QSearchWindow::find()
{
    m_search.Stop();
    filesTable->ClearList();

    QString fileName = "*";//fileComboBox->currentText();
    QString text = textComboBox->currentText();
    QString path = directoryComboBox->currentText();

    PatternsContainer patterns;
    QStringList list = text.split( " ", QString::SkipEmptyParts );

    for( int i = 0; i < list.size(); i++ )
    {
        QString strPattern = list[ i ].trimmed();
        if( strPattern.size() > 0 )
            patterns.push_back( std::string( ( const char* )strPattern.unicode(), strPattern.size() * sizeof( QChar ) ) );
    }

    Masks_t masks;
    QStringList listMasks = fileName.split( ";", QString::SkipEmptyParts );

    for( int i = 0; i < listMasks.size(); i++ )
        masks.push_back( qPrintable( listMasks[ i ].trimmed() ) );

    m_search.Start( qPrintable( path ), patterns, masks );
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
    textComboBox->addItems( SearchGUI::Conf().searches );
    directoryComboBox->addItems( SearchGUI::Conf().searchPaths );
    reloadExtensions();
}

