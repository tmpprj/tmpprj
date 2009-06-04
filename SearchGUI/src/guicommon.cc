#include "guicommon.h"

QStringList GetComboStringList( const QComboBox* pComboBox )
{
    QStringList listElements;

    for( int i = 0; i < pComboBox->count(); i++ )
        listElements << pComboBox->itemText( i );

    return listElements;
}

bool TextExistInCombo( const QComboBox* pComboBox, const QString& str )
{
    QStringList listString = GetComboStringList( pComboBox );
    return listString.contains( str );
}

void ComboInsertCurrentToTop( QComboBox* pComboBox )
{
    if( pComboBox->currentText().isEmpty() )
        return;

    if( TextExistInCombo( pComboBox, pComboBox->currentText() ) )
        return;

    pComboBox->insertItem( 0, pComboBox->currentText() );
}
