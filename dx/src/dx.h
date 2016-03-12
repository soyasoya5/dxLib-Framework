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

	template<typename T>
	byte *bytes_cast( T &t )
	{ return reinterpret_cast<byte*>( &t ); }

	// type traits
	#define CONST_TRUE static const bool value = true
    #define CONST_FALSE static const bool value = false
    #define CONST_TYPEDEF typedef _Ty type 
    
    // ===========================================
    // =			  is_pointer				 =
    // =	if the type is a pointer,            =
    // =    e.g int*, bool* types.				 =
    // ===========================================
    
    template<typename _Ty>
    struct is_pointer { CONST_FALSE; };
    
    template<typename _Ty>
    struct is_pointer<_Ty*> { CONST_TRUE; };
    
    
    // ===========================================
    // =			 is_reference				 =
    // =	if the type is a pointer,            =
    // =    e.g int&, bool& types.				 =
    // ===========================================
    
    template<typename _Ty>
    struct is_reference { CONST_FALSE; };
    
    template<typename _Ty>
    struct is_reference<_Ty&> { CONST_TRUE; };
    
    
    // ===========================================
    // =			    is_array				 =
    // =	if the type is a pointer,            =
    // =    e.g int[], bool[] types.		     =
    // ===========================================
    
    template<typename _Ty>
    struct is_array { CONST_FALSE; };
    
    template<typename _Ty>
    struct is_array<_Ty[]> { CONST_TRUE; };
    
    
    // ===========================================
    // =			 remove_pointer			     =
    // =	if the type is a pointer,            =
    // =    e.g int*, type will be int.			 =
    // ===========================================
    
    template<typename _Ty>
    struct remove_pointer { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_pointer<_Ty*> { CONST_TYPEDEF; };
    
    
    // ===========================================
    // =			 remove_referece			 =
    // =	if the type is a reference,          =
    // =    e.g int&, type will be int.			 =
    // ===========================================
    
    template<typename _Ty>
    struct remove_reference { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_reference<_Ty&> { CONST_TYPEDEF; };
    
    
    // ===========================================
    // =			 remove_array			     =
    // =	if the type is an array,             =
    // =    e.g int[], type will be int.		 =
    // ===========================================
    
    template<typename _Ty>
    struct remove_array { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_array<_Ty[]> { CONST_TYPEDEF; };
    
    // ===========================================
    // =			 remove_all				     =
    // =	if the type is anything but the      =
    // =    type itself, it'll be removed        =
    // =    e.g int[] turns int					 =
    // =    usage: remove_all<int[]>::type var;  =
    // ===========================================
    
    template<typename _Ty>
    struct remove_all { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_all<_Ty*> { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_all<_Ty&> { CONST_TYPEDEF; };
    
    template<typename _Ty>
    struct remove_all<_Ty[]> { CONST_TYPEDEF; };


#undef CONST_TRUE
#undef CONST_FALSE
#undef CONST_TYPEDEF

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

		namespace FileIO
		{
			class Path;
			enum Token_t;
			class Token;
			class Tokenizer;
			struct TokenizerMessage;
		}

		namespace IO
		{
			class _Streambuf;
			class stream;
		}

	}

}

