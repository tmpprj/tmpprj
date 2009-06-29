#ifndef _QFILESTABLE_H_
#define _QFILESTABLE_H_

#include <QTableWidget>

class QFilesTable : public QTableWidget
{
    Q_OBJECT

public:
    QFilesTable( QWidget *parent = 0 );
    void AddFile( const QString& filename, const QString& status, const QColor& statusColor = QColor() );
    void ClearList();

private:
    void mouseMoveEvent( QMouseEvent *event );
};


#endif

