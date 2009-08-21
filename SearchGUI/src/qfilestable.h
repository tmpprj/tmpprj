#ifndef _QFILESTABLE_H_
#define _QFILESTABLE_H_

#include <QTableWidget>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <contextmenu.h>

class QFilesTable : public QTableWidget
{
    Q_OBJECT

public:
    QFilesTable( QWidget *parent = 0 );
    void AddFile( const QString& filename, const QString& status, const QColor& statusColor = QColor() );
    void ClearList();

protected:
    virtual void contextMenuEvent( QContextMenuEvent * e );
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
    virtual void keyPressEvent( QKeyEvent * e );
    void mouseMoveEvent( QMouseEvent *event );
    virtual bool edit( const QModelIndex & index, EditTrigger trigger, QEvent * event );

private Q_SLOTS:
    void headersGeometryChanged();

private:
    QString GetItemFullPath( QTableWidgetItem* pItem );

    CContextMenu m_CtxMenu;
};

class QTestDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QTestDelegate( QWidget* parent = 0 )
        : QStyledItemDelegate( parent )
    {
    }

    virtual QWidget * createEditor ( QWidget * parent, const QStyleOptionViewItem & option, 
            const QModelIndex & index ) const
    {
        QWidget* pWidget = QAbstractItemDelegate::createEditor( parent, option, index );
        QLineEdit* pEdit = qobject_cast< QLineEdit* >( pWidget );
        if( pEdit )
            pEdit->setReadOnly( true );

        return pWidget;
    }  
};


#endif

