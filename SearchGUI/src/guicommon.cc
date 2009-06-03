#include "guicommon.h"

QStringList GetComboStringList( const QComboBox* pComboBox )
{
    QStringList listElements;

    for( int i = 0; i < pComboBox->count(); i++ )
        listElements << pComboBox->itemText( i );

    if( !pComboBox->currentText().isEmpty() &&
            ( pComboBox->count() == 0 || 
              pComboBox->currentText() != pComboBox->itemText( pComboBox->currentIndex() ) ) )
        listElements << pComboBox->currentText();

    return listElements;
}

