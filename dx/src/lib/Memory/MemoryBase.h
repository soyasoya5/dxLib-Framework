#pragma once
#include "Types.h"
#include "../string.h"


begin_MEMORY

		class MemoryBase
		{
		protected:
			__MEMORY Handle<>* _handle;
			__DX uint _pID;
			__LIB String _proc;
			std::vector<__MEMORY Module> _modules;
			bool _can;
		public:
			virtual bool Setup( const __LIB String &_Proc ) = 0;

			virtual bool read_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, byte *_Buff, const __DX uint &_Size ) = 0;
			virtual bool write_bytes( const __MEMORY Module &_Module, const __DX uint &_Offset, byte *_Buff, const __DX uint &_Size ) = 0;
			virtual __MEMORY Module& moduleAt( const __LIB String &_Name );

			template<typename _Type>
			_Type Read( const __MEMORY Module &_Module, const __DX uint &_Addr )
			{
				_Type _Val = _Type( );
				if ( !_can )
					return _Val;
				read_bytes( _Module, _Addr, (byte*)( &_Val ), sizeof(_Type) );
				return _Val;
			}

			template<typename _Type>
			bool Write( const __MEMORY Module &_Module, const __DX uint &_Addr, const _Type &_Val )
			{
				if ( !_can )
					return false;
				return write_bytes( _Module, _Addr, (__DX byte*)( &_Val ), sizeof(_Type) );
			}

			virtual bool isInitalized( ) { return _can; }
		};

end_MEMORY