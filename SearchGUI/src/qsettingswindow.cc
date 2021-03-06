#include <QtCore>
#include <QtGui>
#include <QObject>
#include <macro.h>

#include "qsettingswindow.h"
#include "settings.h"
#include "plaintextextractor.h"
#include "log.h"
#include "searchgui_conf.h"
#include "guicommon.h"

QSettingsWindow::QSettingsWindow( QWidget *parent )
    : QDialog( parent, Qt::WindowContextHelpButtonHint | Qt::Dialog )
{
    setupUi( this );
    
    QStringList labels;
    labels << tr( "File extension" ) << tr( "Parser" );
    tableExtensions->setHorizontalHeaderLabels( labels );
    tableExtensions->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
    tableExtensions->verticalHeader()->hide();
    tableExtensions->setSelectionBehavior( QAbstractItemView::SelectRows );

    tableExtensions->setEditTriggers( tableExtensions->editTriggers() | QAbstractItemView::CurrentChanged  );
    tableExtensions->setShowGrid( true );

    connect( addButton, SIGNAL( clicked() ), this, SLOT( addextension() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( savesettings() ) );
    connect( removeButton, SIGNAL( clicked() ), this, SLOT( removecurrent() ) );

    LoadSettings();
}

void QSettingsWindow::LoadSettings()
{
    FOREACH( p, SearchGUI::Conf().mapExtensions.Value() )
        AddExtension( p.key(), p.value().toString() );
}

void QSettingsWindow::SaveSettings()
{
    SearchGUI::Conf().mapExtensions.Value().clear();

    for( int i = 0; i < tableExtensions->rowCount(); i++ )
    {
        QString strExt = tableExtensions->item( i, 0 )->text().trimmed();
        strExt = FormatExtension( strExt );

        if( strExt.isEmpty() || strExt == "." )
            continue;

        QComboBox* pParserCombo = dynamic_cast< QComboBox* >( tableExtensions->cellWidget( i, 1 ) );
        if( !pParserCombo )
        {
            CLog(Error) << "QSettingsWindow::SaveSettings: pParserCombo is NULL";
            continue;
        }
        QString strParser = pParserCombo->currentText();

        SearchGUI::Conf().mapExtensions.Value()[ strExt ] = strParser; 
    }
}

void QSettingsWindow::InitParserCombo( QComboBox* pParserCombo )
{
    const CTextExtractorFactory::MapNameExtractor_t& mapNameExtractor = 
        TextExtractorFactory::Instance().GetMapNameExtractor();

    CLog(Debug) << "QSettingsWindow::InitParserCombo: Count: " << mapNameExtractor.size();
    FOREACH( p, mapNameExtractor )
        pParserCombo->addItem( p->first );
}

void QSettingsWindow::AddExtension( const QString& strExt, const QString& strParser )
{
    QTableWidgetItem *extensionItem = new QTableWidgetItem( strExt );
    extensionItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable );

    QComboBox* pParserCombo = new QComboBox( this );
    InitParserCombo( pParserCombo );
    int nParserIndex = pParserCombo->findText( strParser );
    if( nParserIndex != -1 )
        pParserCombo->setCurrentIndex( nParserIndex );

    int row = tableExtensions->rowCount();
    tableExtensions->insertRow(row);
    tableExtensions->setItem( row, 0, extensionItem );
    tableExtensions->setCellWidget( row, 1, pParserCombo );

    tableExtensions->setFocus( Qt::TabFocusReason );
    tableExtensions->setCurrentCell( row, 0 );
}

void QSettingsWindow::addextension()
{
    AddExtension( "", "" );
}

void QSettingsWindow::savesettings()
{
    SaveSettings();
    Q_EMIT settingsChanged();

    close();
}

void QSettingsWindow::removecurrent()
{
    tableExtensions->removeRow( tableExtensions->currentRow() );
}

