#ifndef MENUWRAPPER_HPP
#define MENUWRAPPER_HPP

#ifdef WIN32
class CMenuWrapper
{
public:

    CMenuWrapper( HMENU hMenu ):m_hMenu( hMenu )
    {
    }

    ~CMenuWrapper()
    {
        if( INVALID_HANDLE_VALUE != m_hMenu )
            ::DestroyMenu( m_hMenu );
    }

    HMENU Get()
    {
        return m_hMenu;
    }

private:

    HMENU m_hMenu;
};
#endif


#endif // MENUWRAPPER_HPP
