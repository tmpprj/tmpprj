#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QtCore>

QSettings& Settings();

template < class T > class ConfParam
{
    QString m_strKey;
    T m_value;

public:
    ConfParam( const QString& strKey )
        : m_strKey( strKey )
    {
        m_value = Settings().value( strKey ).value< T >();
    }

    T& Value()
    {
        return m_value;
    }

    ~ConfParam()
    {
        Settings().setValue( m_strKey, m_value );
    }
};

#endif

