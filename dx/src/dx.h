#pragma once
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <memory>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <typeindex>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <list>
#include <sstream>
#include <Windows.h> // aka <cancer.h>

#ifdef SendMessage
#undef SendMessage
#endif

namespace dx {
	typedef unsigned int uint;
	typedef unsigned long ulong;
	typedef unsigned char byte;

	template<typename _Type>
	class ScopeExit
	{
		_Type *_val;
		std::function<void(_Type*)> _dest;
	public:
		ScopeExit( _Type *_Val, std::function<void(_Type*)> _Destructor )
		{
			_val = _Val;
			_dest = _Destructor;
		}
	
		~ScopeExit( )
		{
			if ( _dest )
				_dest( _val );
		}
	
	};

	namespace lib {
		class String;
		template<typename T>
		class Iterator;
		template<typename T>
		class ReverseIterator;
		class AsyncKeeper;
		class AsyncGuard;
		class FlexibleGuard;
		namespace Memory {
			struct Destructor { };
			struct LiveFor { };
			class Module;
			template<typename _Lifetime = Destructor,
				uint _Delay = static_cast<uint>(-1)>
			class Handle;
			class MemoryBase;
			class InternalImpl;
			class ExternalImpl;
			class Address;
			class Pattern;
		}

	}

}

