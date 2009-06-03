#include <QtGui>
#include "qsettingswindow.h"
#include "settings.h"
#include "plaintextextractor.h"
#include "log.hpp"

QSettingsWindow::QSettingsWindow( QWidget *parent )
    : QDialog( parent )
{
    setupUi( this );
    
    QStringList labels;
    labels << tr( "File extension" ) << tr( "Parser" );
    tableExtensions->setHorizontalHeaderLabels( labels );
    tableExtensions->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
    tableExtensions->verticalHeader()->hide();
    tableExtensions->setShowGrid( true );

    connect( addButton, SIGNAL( clicked() ), this, SLOT( addext() ) );
    
    QMap< QString, QVariant > mapExtensions = Settings().value( "extensions" ).toMap();
    for( QMap< QString, QVariant >::iterator p = mapExtensions.begin(); p != mapExtensions.end(); p++ )
        AddExtension( p.key(), p.value().toString() );
}

void QSettingsWindow::InitParserCombo( QComboBox* pParserCombo )
{
    const CTextExtractorFactory::MapNameExtractor_t& mapNameExtractor = 
        TextExtractorFactory::Instance().GetMapNameExtractor();

    CLog() << "Count: " << mapNameExtractor.size() << std::endl;
    for( CTextExtractorFactory::MapNameExtractor_t::const_iterator p = mapNameExtractor.begin();
            p != mapNameExtractor.end(); p++ )
        pParserCombo->addItem( p->first.c_str() );
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
}

void QSettingsWindow::addext()
{
    AddExtension( "", "" );
}

