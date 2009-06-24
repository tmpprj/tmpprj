#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/filesystem.hpp>
#include <QString>
#include <singleton.hpp>
#include <mt_queue.hpp>
#include <datahandler.hpp>

class CPlainTextExtractor: public CDataHandler< QString >
{
public:

    struct structFileData
    {
        QString strFileName;
        QString strFileData;
    };

    boost::signal1< void, const structFileData& >& SigDataObtained();

private:

    virtual void WorkerFunc( const QString& strFileName );

    boost::signal1< void, const structFileData& > m_sigDataObtained;
};

class ITextExtractor: public boost::noncopyable
{
public:

    virtual ~ITextExtractor(){}

    virtual void Extract( const QString& strFileNmae, QString& strText ) = 0;
};

class CTextExtractorFactory
{
public:
    CTextExtractorFactory();

    ~CTextExtractorFactory();

    ITextExtractor* GetExtractor( const QString& strFileName );

    bool RegisterName( const QString& strName, ITextExtractor* pTextExtractor );
    bool RegisterExtension( const QString& strExtension, const QString& strName );
    void ClearExtensions();

    typedef std::map< QString, QString > MapExtensionName_t;
    const MapExtensionName_t& GetMapExtensionName();
    
    typedef std::map< QString, ITextExtractor* > MapNameExtractor_t;
    const MapNameExtractor_t& GetMapNameExtractor();

private:
    MapNameExtractor_t m_mapNameExtractor;

    MapExtensionName_t m_mapExtensionName;

    ITextExtractor* m_pDefaultExtractor;
};

typedef Singleton<CTextExtractorFactory> TextExtractorFactory;

#endif // CPLAINTEXTEXTRACTOR_H
