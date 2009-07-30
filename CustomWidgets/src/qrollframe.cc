#include "qrollframe.h"
#include <QtGui>


QRollFrame::QRollFrame( QWidget* parent )
    : QFrame( parent )
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget( &m_button );
    for( int i = 0; i < children().size(); i++ )
    {
        QWidget* pWidget = dynamic_cast< QWidget* >( children().at( i ) );
        if( pWidget )
           layout->addWidget( pWidget );
        qDebug() << "WIDGET";
    }

    setLayout( layout );
}
