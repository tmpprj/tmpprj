#ifndef _FILESTABLE_H_
#define _FILESTABLE_H_

#include <QTableWidget>

class QFilesTable : public QTableWidget
{
    Q_OBJECT

public:
    QFilesTable( QWidget *parent = 0 );
    void AddFile( const QString& filename );
    void ClearList();

private:
    void mouseMoveEvent( QMouseEvent *event );
};


#endif

