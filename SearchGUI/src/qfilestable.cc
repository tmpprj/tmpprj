#include <QtGui>
#include "qfilestable.h"

QFilesTable::QFilesTable( QWidget *parent )
    : QTableWidget( 0, 2, parent )
    , m_CtxMenu( winId() )
{
    QStringList labels;
    labels << tr( "File Name" ) << tr( "Status" );
    setHorizontalHeaderLabels( labels );

    horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );

    verticalHeader()->hide();
    setShowGrid( true );
}

void QFilesTable::AddFile( const QString& filename, const QString& status, const QColor& statusColor )
{
    QTableWidgetItem *fileNameItem = new QTableWidgetItem( filename );
    fileNameItem->setFlags(Qt::ItemIsEnabled);

    QTableWidgetItem *statusItem = new QTableWidgetItem( status );
    statusItem->setFlags(Qt::ItemIsEnabled);

    if( statusColor.isValid() )
        statusItem->setData( Qt::BackgroundColorRole, statusColor );
    
    int row = rowCount();
    insertRow(row);
    setItem( row, 0, fileNameItem );
    setItem( row, 1, statusItem );
}

void QFilesTable::ClearList()
{
    clearContents();
    setRowCount( 0 );
}

void QFilesTable::contextMenuEvent ( QContextMenuEvent * e )
{
    QTableWidgetItem* pItem;
    if( NULL != ( pItem = itemAt( e->pos() ) ) && 0 == pItem->column() )
        m_CtxMenu.Show( e->pos(), pItem->text() );
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

