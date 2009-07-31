#include "include/qrollframe.h"
#include <QtGui>
#include <QMessageBox>

QRollFrame::QRollFrame( QWidget* parent )
    : QWidget( parent )
    , m_stack( this )
    , m_button( this )
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget( &m_button );
    layout->addWidget( &m_stack );
    setLayout( layout );

    connect( &m_button, SIGNAL(clicked()), this, SLOT(buttonPushed()) );
}

void QRollFrame::buttonPushed()
{
    QMessageBox::warning(NULL, "test", "buttonPushed" );
//    m_stack.widget(0)->hide();
}

void QRollFrame::addPage(QWidget *page)
{
//    QMessageBox::warning( NULL, "test", "count=" + QString::number( m_stack.count() ) + " index=" + QString::number( m_stack.currentIndex() ) );
    page->setParent(&m_stack);
    m_stack.insertWidget(0, page );
}

QWidget* QRollFrame::widget( int index )
{
    return m_stack.widget( index );
}
