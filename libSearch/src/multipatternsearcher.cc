#include "multipatternsearcher.h"

#include <stdexcept>
#include <sstream>
#include <log.hpp>

#define mm          8191


using namespace std;

MultiPatternSearcher::MultiPatternSearcher()
{
    LONG = 0;
    SHORT = 0;
    pt = NULL;
    qt = NULL;
}

void MultiPatternSearcher::PreparePattern( int nIndex )
{
    register unsigned int hash, Mask = HASH_SHIFT;
    
    string& strPattern = m_vPatternInfo[ nIndex ].strPattern;
    
    for( int i = m_nMinPatternSize - 1; i >= ( 1 + LONG ); i-- ) 
    {
        hash = ( strPattern[ i ] & Mask );
        hash = ( hash << HASH_SHIFT ) + ( strPattern[ i - 1] & Mask ) ;
        if( LONG ) 
            hash = ( hash << HASH_SHIFT ) + ( strPattern[ i - 2 ] & Mask );
        if( SHIFT1[ hash ] >= m_nMinPatternSize - 1 - i ) 
            SHIFT1[ hash ] = m_nMinPatternSize - 1 - i;
    }
    
    if( SHORT ) 
        Mask = 255;
    hash = 0;
    for( int i = m_nMinPatternSize - 1; i >= 0; i-- )
        hash = ( hash << HASH_SHIFT ) + ( tr[ ( unsigned char )strPattern[ i ] ] & Mask );

    hash = hash & mm;
    qt = ( struct pat_list* )malloc( sizeof( struct pat_list ) );
    qt->index = nIndex;
    pt = HASH[ hash ];
    qt->next = pt;
    HASH[ hash ] = qt;
}

void MultiPatternSearcher::LoadPatterns( const PatternsContainer& vPatterns )
{
    unsigned Mask = HASH_SHIFT;
    
    // Clear data
    m_vPatternInfo.clear();
    m_vPatternsLengths.clear();

    if( vPatterns.size() == 0 )
        return;
    
    for( size_t i = 0; i < MAXSYM; i++ ) 
        tr[ i ] = i;
    
    for( size_t i = 0; i < MAXSYM; i++ ) 
        tr1[i] = tr[ i ] & Mask;
    
    int nTotalDataLength = 0;
    m_nMinPatternSize = 0;
    
    m_vPatternInfo.reserve( vPatterns.size() );
    
    for( size_t i = 0; i < vPatterns.size(); i++ )
    {
        if( vPatterns[ i ].size() == 0 )
            continue;
   
        m_vPatternsLengths.push_back( ( int )vPatterns[ i ].size() );
        if( m_nMinPatternSize == 0 )
            m_nMinPatternSize = ( int )vPatterns[ i ].size();
        else
            m_nMinPatternSize = min( m_nMinPatternSize, 
                                     ( int )vPatterns[ i ].size() );
        nTotalDataLength += vPatterns[ i ].size();
        
        PatternInfo info = { vPatterns[ i ], 0 };
        m_vPatternInfo.push_back( info );
    }

        
    if( m_vPatternInfo.size() == 0 )
    {
        CLog(debug) << "There are no valuable patterns" << std::endl;
        return;
    }
    
    if( nTotalDataLength > 400 && m_nMinPatternSize > 2 ) 
        LONG = 1;
    if( m_nMinPatternSize == 1 ) 
        SHORT = 1;
    
    for( size_t i = 0; i < MAXMEMBER1; i++ ) 
        SHIFT1[ i ] = m_nMinPatternSize - 2;
    
    for( size_t i = 0; i < MAXHASH; i++ )
        HASH[ i ] = 0;
    
    for( size_t i = 0; i < m_vPatternInfo.size(); i++ )
        PreparePattern( i );
}

int MultiPatternSearcher::AlgorithmMonkey( unsigned char* text, int start, int end )
{
    register unsigned char* textend;
    register unsigned int hash, i;
    register unsigned char shift; 
    register int  m1, j, Long = LONG; 
    int pat_index, m = m_nMinPatternSize; 
    int MATCHED = 0;
    register unsigned char *qx;
    register struct pat_list *p;
    unsigned char *lastout;

    int retWeight = 0;
    
    textend = text + end;
    m1 = m - 1;
    lastout = text + start + 1;
    text = text + start + m1 ;
    
    PatternInfo* lpPatternInfo = &m_vPatternInfo[ 0 ];
    int* lpPatternLengths = &m_vPatternsLengths[ 0 ];
    
    static int nUpdateId = 0;
    nUpdateId++;

    while( text <= textend ) 
    {
        hash = tr1[ *text ];
        hash = ( hash << HASH_SHIFT ) + ( tr1[ *( text - 1 ) ] );
        if( Long ) 
            hash = ( hash << HASH_SHIFT ) + ( tr1[ *( text - 2 ) ] );
        shift = SHIFT1[ hash ];
        
        if( shift == 0 ) 
        {
            hash=0;
            
            for( i = 0; i <= ( unsigned int )m1; i++ )  
                hash = ( hash << HASH_SHIFT ) + ( tr1[ *( text - i ) ] );
            
            hash = hash & mm;
            p = HASH[ hash ];
            
            while( p != 0 ) 
            {
                pat_index = p->index;
                p = p->next;
                qx = text-m1;
                j = 0;
                while( tr[ ( unsigned char )*( lpPatternInfo[ pat_index ].strPattern.c_str()
                        + j ) ] == tr[ *( qx++ ) ] )
                    j++;
                
                if (j > m1 ) 
                {
                    if( lpPatternLengths[ pat_index ] <= j ) 
                        if( nUpdateId != lpPatternInfo[ pat_index ].nUpdateId )
                        {
                            retWeight++;
                            lpPatternInfo[ pat_index ].nUpdateId = nUpdateId;
                        }
                }
            }
            
            if( !MATCHED ) 
                shift = 1;
            else 
            {
                MATCHED = 0;
                shift = m1;
            }
        }
        text = text + shift;
    }
    
    return retWeight;
}

int MultiPatternSearcher::AlgorithmShort( unsigned char* text, int start, int end )
{
    register unsigned char *textend;
    register int  j; 
    register struct pat_list *p;
    register int pat_index; 
    int MATCHED = 0;
    unsigned char *lastout;
    unsigned char *qx;
    
    int retWeight = 0;
    
    textend = text + end;
    lastout = text + start + 1;
    text = text + start - 1 ;
    
    PatternInfo* lpPatternInfo = &m_vPatternInfo[ 0 ];
    int* lpPatternLengths = &m_vPatternsLengths[ 0 ];

    static int nUpdateId = 0;
    nUpdateId++;

    while( ++text <= textend ) 
    {
        p = HASH[ *text ];
        
        while( p != 0 ) 
        {
            pat_index = p->index;
            p = p->next;
            qx = text;
            j = 0;
            while( tr[ ( unsigned char )*( lpPatternInfo[ pat_index ].strPattern.c_str() 
                   + j ) ] == tr[ *( qx++ ) ] )
                j++;
            
            if( lpPatternLengths[ pat_index ] <= j ) 
                if( nUpdateId != lpPatternInfo[ pat_index ].nUpdateId )
                {
                    retWeight++;
                    lpPatternInfo[ pat_index ].nUpdateId = nUpdateId;
                }
        }
        MATCHED = 0;
    }
    
    return retWeight;
}

int MultiPatternSearcher::FindPatterns( const std::string& strText )
{
    if( m_vPatternInfo.size() == 0 )
        return 0;
    
    if( SHORT )
        return AlgorithmShort( ( unsigned char* )strText.c_str(), 0, strText.size() - 1 );
    else
        return AlgorithmMonkey( ( unsigned char* )strText.c_str(), 0, strText.size() - 1 );
}

size_t MultiPatternSearcher::GetPatternCount()
{
    return m_vPatternInfo.size();
}

