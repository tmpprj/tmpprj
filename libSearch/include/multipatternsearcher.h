#ifndef _MULTIPATTERNSEARCHER_H_
#define _MULTIPATTERNSEARCHER_H_

#include <vector>
#include <string>
#include <set>
#include <map>

#define MAXMEMBER1  4096

#define MAXHASH     8192

#define MAXSYM      256
#define HASH_SHIFT  4
#define HASH_MASK   15

typedef std::vector< std::string > PatternsContainer;
typedef std::set< std::string > PatternMatchContainer;

struct PatternInfo
{
    std::string strPattern;
    int nUpdateId;
};

typedef std::vector< PatternInfo > PatternsInfoContainer;

class MultiPatternSearcher
{
    int LONG;
    int SHORT;
    unsigned char SHIFT1[ MAXMEMBER1 ];
    unsigned char tr[ MAXSYM ];
    unsigned char tr1[ MAXSYM ];
    struct pat_list 
    {
        int  index;
        struct pat_list *next;
    } *HASH[ MAXHASH ];
    
    struct pat_list *pt, *qt;
    
    PatternsInfoContainer m_vPatternInfo;
  
    std::vector< int > m_vPatternsLengths;
    int m_nMinPatternSize;
    int nUpdateId;
    
    void PreparePattern( int nIndex );
    int AlgorithmMonkey( unsigned char* text, int start, int end, PatternMatchContainer& matches );
    int AlgorithmShort( unsigned char* text, int start, int end, PatternMatchContainer& matches );
    
public:  
    MultiPatternSearcher();
    void LoadPatterns( const PatternsContainer& vPatterns );
    int FindPatterns( const std::string& strText, PatternMatchContainer& matches );
    int FindPatterns( const std::string& strText );
    size_t GetPatternCount();
};

#endif
