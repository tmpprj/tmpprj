#ifndef CPLAINTEXTEXTRACTOR_H
#define CPLAINTEXTEXTRACTOR_H

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
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

    boost::signals2::signal1< void, const structFileData& >& SigDataObtained();
    boost::signals2::signal1< void, const QString& >& SigFileProcessing();

private:

    virtual void WorkerFunc( const QString& strFileName );

    boost::signals2::signal1< void, const structFileData& > m_sigDataObtained;
    boost::signals2::signal1< void, const QString& > m_sigFileProcessing;
};

class ITextExtractor: public boost::noncopyable
{
public:

    virtual ~ITextExtractor(){}

    virtual void Extract( const QString& strFileNmae, QString& strText ) = 0;

    const QString& GetName()
    {
        return m_strName;
    }

protected:

    QString m_strName;

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
