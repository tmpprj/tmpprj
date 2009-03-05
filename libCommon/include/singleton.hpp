//@(#) Singleton template
// Author: Dmitry Parshin
// Edited: Eugene Bolotin
// Licence: LGPLv3

#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

///\class Singleton
///\brief Singleton template

template< class T >
class Singleton
{
public:
    static T& Instance ()
    {
	static T instance;
	return instance;
    }
};


#endif
