#include <stdexcept>
#include <errno.h>


class CUserLevelError: public std::exception
{
public:
    
    CUserLevelError( const QString& strDescr ):m_strDescr( strDescr )
    {}

    CUserLevelError()
    {
		m_strDescr = ::strerror (errno);
    }

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
