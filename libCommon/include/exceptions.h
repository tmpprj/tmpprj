#include <stdexcept>


class CUserLevelError: public std::exception
{
public:
    
    CUserLevelError( const QString& strDescr ):m_strDescr( strDescr )
    {}

    virtual ~CUserLevelError() throw()
    {}

    virtual const char* what() const throw()
    {
        return m_strDescr.toAscii().constData();
    }

    const QString& whatQ() const
    {
        return m_strDescr;
    }

private:

    QString m_strDescr;
};
