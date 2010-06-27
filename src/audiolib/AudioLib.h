/**
 * @class AudioLib
 * @brief Provides a generic Factory class pattern.
 *
 * Implements a generic class factory. Classes should register themselves with
 * the class factory immediately, so they are available for use in the main()
 * routine. To allow a class to be instantiated by the factory, the following
 * are required in each class definition:
 *   static Component* create() {return new [derivedclass];}
 *   static int init;
 * and outside the class:
 *   [derivedclass]::init 
 *   		= Factory<Param_type,std::string>::RegisterCreatorFunction(
 *   				"[derivedclass]",[derivedclass]::create
 *   		  );
 * So, we have a static create function to actually create an instance of this
 * class, and the static init dummy variable is used to force the class to
 * register immediately on execution.
 *
 * To create an instance of a derived class, for instance:
 * Component* var_name =
 * Factory<_Param,std::string>
 * 				::CreateInstance("[derivedclass]",Parameter)
 */
#ifndef CLASS_AUDIOLIB
#define CLASS_AUDIOLIB

#include <map>
#include "Component.h"

typedef Audio::Component _Base;
typedef std::string _Key;

template <	typename _Param,			// Type of param to pass to constructor
			typename _Predicator = std::less<_Key> >
class AudioLib {
	public:
		/// Constructor
		AudioLib() {}
		/// Destructor
		~AudioLib() {}

		/// typedef for the creator function, return of type base class.
    	typedef _Base* (*CreatorFunction) (_Param);
		/// Shorthand for our map
	    typedef std::map<_Key, CreatorFunction, _Predicator> _mapFactory;
		/// typename for our maps iterator
		typedef typename _mapFactory::iterator _mapFactoryIterator;

		/// Create an instance of the class referred to by \c idKey
	    static _Base* CreateInstance(_Key idKey, _Param x) {
			_mapFactoryIterator it = get_mapFactory()->find(idKey);
	        if (it != get_mapFactory()->end()) {
	            if (it->second) {
	                return it->second(x);
    	        }
        	}
			return NULL;
    	}

		/// Register a class with the factory
		static _Key RegisterCreatorFunction(_Key idKey, 
											CreatorFunction classCreator) {
		    get_mapFactory()->insert(std::pair<_Key,CreatorFunction>
													(idKey, classCreator));
        	return idKey;
		}

	protected:
		/// Static function to return the map, ensures it is created first.
	    static _mapFactory * get_mapFactory() {
	        static _mapFactory m_sMapFactory;
	        return &m_sMapFactory;
	    }
};

#endif
