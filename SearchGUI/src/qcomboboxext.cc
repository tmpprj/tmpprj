#include "qcomboboxext.h"


QComboBoxExt::QComboBoxExt( QWidget* parent )
    : QComboBox( parent )
{
    m_palDefault = palette();
    m_palTooltip = m_palDefault;
    m_palTooltip.setColor( QPalette::Text, qRgb( 192, 192, 192 ) );

    connect( this, SIGNAL( editTextChanged( const QString& ) ), this, SLOT( textChanged() ) );
    CheckEmptyText();
}

void QComboBoxExt::PushTextToList( const QString& str )
{
    if( str.isEmpty() )
        return;
    
    QStringList list = GetElements();
    int iIdx = list.indexOf( str );
    if( -1 != iIdx )
    {
        setCurrentIndex( iIdx );
        return;
    }

    insertItem( 0, str );
    setCurrentIndex( 0 );
}

void QComboBoxExt::PushCurrentToList()
{
    PushTextToList( GetCurrentText() );
}

QStringList QComboBoxExt::GetElements()
{
    QStringList list;

    for( int i = 0; i < count(); i++ )
        list << itemText( i );

    return list;
}

QStringList QComboBoxExt::GetFullElements()
{
    QStringList list = GetElements();
    list.push_front( GetCurrentText() );

    return list;
}

void QComboBoxExt::SetFullElements( const QStringList& list )
{
    if( list.empty() )
        setEditText( m_strDefault );
    else
    {
        for( int i = 1; i < list.size(); i++ )
            addItem( list[ i ] );

        setEditText( list[ 0 ] );
    }
    CheckEmptyText();
}

void QComboBoxExt::SetDefaultElement( const QString& strDefault )
{
    m_strDefault = strDefault;
    PushTextToList( strDefault );
}

QString QComboBoxExt::GetCurrentText()
{
    if( currentText() == toolTip() )
        return "";
    else
        return currentText();
}

void QComboBoxExt::textChanged()
{
    if( toolTip().isEmpty() )
        return;

    if( currentText() == toolTip() )
        setPalette( m_palTooltip );
    else
        setPalette( m_palDefault );
}

void QComboBoxExt::setDisabled( bool disable )
{
    if( disable )
    {
        m_strHiddenText = currentText();
        setEditText( "" );
    }
    else
        setEditText( m_strHiddenText );

    QComboBox::setDisabled( disable );
}

void QComboBoxExt::CheckEmptyText()
{
    if( toolTip().isEmpty() )
        return;
    
    if( currentText().isEmpty() )
        setEditText( toolTip() );
}

void QComboBoxExt::focusInEvent( QFocusEvent * event )
{
    if( currentText() == toolTip() )
        setEditText( "" );
    QComboBox::focusInEvent( event );
}

void QComboBoxExt::focusOutEvent( QFocusEvent * event )
{
    CheckEmptyText();
    QComboBox::focusOutEvent( event );
}
