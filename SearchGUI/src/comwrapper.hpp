#ifndef COMWRAPPER_HPP
#define COMWRAPPER_HPP

template< class ComType >
class CComWrapper
{
public:

    CComWrapper():m_pComObj( NULL )
    {}

    CComWrapper( ComType* pComObj ):m_pComObj( pComObj )
    {
    }

    ~CComWrapper()
    {
        Clear();
    }

    ComType* Get()
    {
        return m_pComObj;
    }

    ComType** Set()
    {
        Clear();
        return &m_pComObj;
    }

    void Clear()
    {
        if( NULL != m_pComObj )
        {
            m_pComObj->Release();
            m_pComObj = NULL;
        }
    }

private:


    ComType* m_pComObj;
};


#endif // COMWRAPPER_HPP
