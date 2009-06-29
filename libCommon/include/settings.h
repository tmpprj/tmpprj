#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QtCore>

QSettings& Settings();

template < class T > class ConfParam
{
    QString m_strKey;
    T m_value;

public:
    ConfParam( const QString& strKey, const QString& strDefault = "" )
        : m_strKey( strKey )
    {
        QVariant var = Settings().value( strKey, strDefault );
        m_value = var.value< T >();
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

