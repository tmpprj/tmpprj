#include <QtGui>
#include "qfilestable.h"
#include <log.h>


QFilesTable::QFilesTable( QWidget *parent )
    : QTableWidget( 0, 3, parent )
    , m_CtxMenu( winId() )
{
    QStringList labels;
    labels << tr( "FileName" ) << tr( "Folder" ) << tr( "Status" );
    setHorizontalHeaderLabels( labels );

    horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );

    connect( horizontalHeader(), SIGNAL( geometriesChanged() ), this, SLOT( headersGeometryChanged() ) );

    verticalHeader()->hide();
    setShowGrid( true );

    setEditTriggers( QAbstractItemView::SelectedClicked );
    
    setSelectionMode( QAbstractItemView::SingleSelection );
    setSelectionBehavior( QAbstractItemView::SelectItems );
    setItemDelegate( new QTestDelegate( this ) );
}

void QFilesTable::AddFile( const QString& filename, const QString& status, const QColor& statusColor )
{
    QString filenameFmtUnix = QDir::fromNativeSeparators( filename );
    int nIndex = filenameFmtUnix.lastIndexOf( '/' );
    QString strFile = filename.mid( nIndex + 1 );
    QString strPath = filename.left( nIndex + 1 );
    
    QDir file( filename );

    QTableWidgetItem *fileNameItem = new QTableWidgetItem( strFile );
    fileNameItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable );
    fileNameItem->setToolTip( strFile );

    QTableWidgetItem *pathNameItem = new QTableWidgetItem( strPath );
    pathNameItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    pathNameItem->setToolTip( strPath );

    QTableWidgetItem *statusItem = new QTableWidgetItem( status );
    statusItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    statusItem->setToolTip( status );

    if( statusColor.isValid() )
        statusItem->setData( Qt::BackgroundColorRole, statusColor );
    
    int row = rowCount();
    insertRow(row);
    setItem( row, 0, fileNameItem );
    setItem( row, 1, pathNameItem );
    setItem( row, 2, statusItem );
}

void QFilesTable::ClearList()
{
    clearContents();
    setRowCount( 0 );
}

void QFilesTable::contextMenuEvent( QContextMenuEvent * e )
{
    QTableWidgetItem* pItem;
    if( NULL != ( pItem = itemAt( e->pos() ) ) && 2 != pItem->column() )
        m_CtxMenu.Show( e->globalPos(), GetItemFullPath( pItem ) );
    QTableWidget::contextMenuEvent( e );
}

void QFilesTable::mouseDoubleClickEvent( QMouseEvent * e )
{
    QTableWidgetItem* pItem;
    if( NULL != ( pItem = itemAt( e->pos() ) ) && 2 != pItem->column() )
        m_CtxMenu.InvokeDefault( GetItemFullPath( pItem ) );
    QTableWidget::mouseDoubleClickEvent( e );
}

void QFilesTable::keyPressEvent( QKeyEvent * e )
{
    if( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return )
    {
        QTableWidgetItem* pItem = currentItem();
        if( NULL != pItem && 2 != pItem->column() )
            m_CtxMenu.InvokeDefault( GetItemFullPath( pItem ) );
    }
    QTableWidget::keyPressEvent(e);
}

void QFilesTable::mouseMoveEvent( QMouseEvent *event )
{
    if( !currentItem() )
        return QTableWidget::mouseMoveEvent( event );

    if( !( event->buttons() & Qt::LeftButton ) )
        return QTableWidget::mouseMoveEvent( event );
    
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
    
    QTableWidget::mouseMoveEvent( event );
}

bool QFilesTable::edit( const QModelIndex & index, EditTrigger trigger, QEvent * event )
{
    CLog( Debug ) << "edit called: " << ( int )trigger << " coord: " << index.row() << ", " << index.column();
    CLog( Debug ) << "Selection model: " << selectionModel()->isSelected( index );

/*    if( trigger != QAbstractItemView::SelectedClicked )
    {
        m_edit.hide();
        return QTableWidget::edit( index, trigger, event );
    }
*/
    return QTableWidget::edit( index, trigger, event );
}

void QFilesTable::headersGeometryChanged()
{
    horizontalHeader()->setResizeMode( 0, QHeaderView::Interactive );
    horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch);
    horizontalHeader()->setResizeMode( 2, QHeaderView::Interactive );
}

QString QFilesTable::GetItemFullPath( QTableWidgetItem* pItem )
{
    if( pItem->column() == 0 )
        return item( pItem->row(), 1 )->text() + pItem->text();
    else if( pItem->column() == 1 )
        return item( pItem->row(), 1 )->text();

    return "";
}

