#ifndef _QFILESTABLE_H_
#define _QFILESTABLE_H_

#include <QTableWidget>
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

private:

    void mouseMoveEvent( QMouseEvent *event );

    CContextMenu m_CtxMenu;
};


#endif

