#include <QtGui>
#include "qsettingstable.h"

QExtensionsTable::QExtensionsTable( QWidget *parent )
    : QTableWidget( parent )
{
    QStringList labels;
    labels << tr( "Extension" ) << tr( "Parser" );
    setHorizontalHeaderLabels( labels );
    horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    verticalHeader()->hide();
    setShowGrid( true );
}

void QExtensionsTable::AddExtension( const QString& ext, const QString& parser )
{
    QTableWidgetItem *extensionItem = new QTableWidgetItem( ext );
    extensionItem->setFlags( Qt::ItemIsEnabled );
    QTableWidgetItem *parserItem = new QTableWidgetItem( parser );
    parserItem->setFlags( Qt::ItemIsEnabled );

    int row = rowCount();
    insertRow(row);
    setItem( row, 0, extensionItem );
    setItem( row, 1, parserItem );
}

void QExtensionsTable::RemoveCurrent()
{

}

void QExtensionsTable::ClearList()
{
    clearContents();
    setRowCount( 0 );
}
