#ifndef _QSETTINGSTABLE_H_
#define _QSETTINGSTABLE_H_

#include <QTableWidget>

class QExtensionsTable : public QTableWidget
{
    Q_OBJECT

public:
    QExtensionsTable( QWidget *parent = 0 );
    void AddExtension( const QString& ext, const QString& parser );
    void RemoveCurrent();
    void ClearList();
};


#endif

