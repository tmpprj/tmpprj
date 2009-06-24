#include "guicommon.h"

#include <macro.h>
#include <boost/foreach.hpp>
#include <log.hpp>

QStringList GetComboStringList( const QComboBox* pComboBox, bool bPutCurrentToTop )
{
    QStringList listElements;

    if( bPutCurrentToTop )
        listElements << pComboBox->currentText();

    for( int i = 0; i < pComboBox->count(); i++ )
    {
        if( bPutCurrentToTop )
           if( pComboBox->itemText( i ) == pComboBox->currentText() )
               continue;
        listElements << pComboBox->itemText( i );
    }

    return listElements;
}

void LoadStringListToCombo( QComboBox* pComboBox, const QStringList& list )
{
    pComboBox->clear();
    BOOST_FOREACH( QString str, list )
        if( !str.isEmpty() )
            pComboBox->addItem( str );
}

void MoveCurrentToTop( QComboBox* pComboBox )
{
    QStringList list = GetComboStringList( pComboBox, true );
    LoadStringListToCombo( pComboBox, list );
}

void ParsePatterns( const QString& text, QStringList& listPatterns )
{
    int nStart = 0;
    bool bCommaBlock = false;

    for( int i = 0; i <= text.size(); i++ )
        if( i == text.size() )
        {
            if( !bCommaBlock )
                listPatterns.push_back( text.mid( nStart, i - nStart ).trimmed() );
        }
        else if( text[ i ] == '"' )
        {
            if( bCommaBlock )
                listPatterns.push_back( text.mid( nStart, i - nStart ).trimmed() );

            bCommaBlock = !bCommaBlock;
            nStart = i + 1;
        }
        else if( text[ i ] == ' ' )
        {
            if( !bCommaBlock )
            {
                listPatterns.push_back( text.mid( nStart, i - nStart ).trimmed() );
                nStart = i + 1;
            }
        }
}

