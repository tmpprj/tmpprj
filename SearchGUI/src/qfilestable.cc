#include <QtGui>
#include "qfilestable.h"

QFilesTable::QFilesTable( QWidget *parent )
    : QTableWidget( 0, 1, parent )
{
    QStringList labels;
    labels << tr("File Name");
    setHorizontalHeaderLabels(labels);
    horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    verticalHeader()->hide();
    setShowGrid( true );
}

void QFilesTable::AddFile( const QString& filename )
{
    QTableWidgetItem *fileNameItem = new QTableWidgetItem( filename );
    fileNameItem->setFlags(Qt::ItemIsEnabled);

    int row = rowCount();
    insertRow(row);
    setItem( row, 0, fileNameItem );
}

void QFilesTable::ClearList()
{
    clearContents();
    setRowCount( 0 );
}

void QFilesTable::mouseMoveEvent( QMouseEvent *event )
{
    if( !currentItem() )
        return;

    if( !( event->buttons() & Qt::LeftButton ) )
        return;
    
    QDrag *drag = new QDrag( this );
    QMimeData *mimeData = new QMimeData;

    QList<QUrl> list;
#ifdef WIN32
    list.append( QUrl( "file:/" + currentItem()->text() ) );
#else
    list.append( QUrl( "file://" + currentItem()->text() ) );
#endif
    
    mimeData->setUrls( list ); 
    
    drag->setMimeData( mimeData );
    drag->start( Qt::CopyAction );
}

