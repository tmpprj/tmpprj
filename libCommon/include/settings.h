#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QtCore>
#include <boost/function.hpp>
#include <log.h>

QSettings& Settings();

template< class T >
class BoundsValidator
{
public:

    BoundsValidator( T minValue, T maxValue )
        :m_minValue( minValue )
        ,m_maxValue( maxValue )
    {}

    bool operator()( T& Value )
    {
        return Value >= m_minValue && Value <= m_maxValue;
    }

private:

    T m_minValue, m_maxValue;
};


template < class T > class ConfParam
{
    QString m_strKey;
    T m_value;

public:

    //If validator has successfully loaded parameter (fixed and loaded) than it returns true,
    //otherwise it returns false and default value is used
    ConfParam( const QString& strKey, const QVariant& strDefault = QVariant(), boost::function1< bool, T& > Validator = 0  )
        : m_strKey( strKey )
    {
        QVariant var = Settings().value( strKey, strDefault );
        m_value = var.value< T >();

        if( !Validator.empty() && !Validator( m_value ) )
        {
            CLog( Error ) << "ConfParam::ConfParam: " << strKey << " value is incorrect, setting default";
            m_value = strDefault.value<T>();
        }
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

